#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <pcaudiolib/audio.h>
#include "ext/toml.hpp"
#include "lpmwrapper.hh"

using namespace std;


struct TrackerConf
{
  double freq{400};
  double balance{0.5}; // 0 is left, 1 is right
  std::atomic<int64_t> counter{0};
};


void playerThread(const TrackerConf* tcptr)
{
  auto& counter = tcptr->counter;
  audio_object* ao;
  ao=create_audio_device_object(0, "teller", "");
  if(!ao) {
    cerr<<"Unable to open audio file "<<endl;
    return;
  }
  
  int res = audio_object_open(ao, AUDIO_OBJECT_FORMAT_S16LE, 44100, 2);
  if(res < 0) {
    cerr<<"Error opening audio: "<<audio_object_strerror(ao, res)<<endl;
    return;
  }

  vector<int16_t> data;
  int ourcounter=0;
  data.reserve(44100);
  while(counter >= 0) {
    data.clear();
    if(ourcounter < counter) {
      for(int n=0; n < 250; ++n) {
        int16_t val = 20000 * sin((n/44100.0) * tcptr->freq * 2 * M_PI);
        int16_t lval = tcptr->balance * val;
        int16_t rval = (1.0-tcptr->balance) * val;
        
        data.push_back(lval);
        data.push_back(rval);
      }
      ourcounter++;
      if(counter - ourcounter > 1000)
        ourcounter = counter;
    }
    else {
      for(int n=0; n < 150; ++n) {
        data.push_back(0);
        data.push_back(0);
      }
    }
    
    audio_object_write(ao, &data[0], data.size() * sizeof(decltype(data)::value_type));
    // audio_object_flush(ao);
  }
}


int main(int argc, char** argv)
{
  toml::table conftbl, trackertbl;
  try
    {
      trackertbl = toml::parse_file("trackers.conf");
      conftbl = toml::parse_file("teller.conf");
      //      std::cout << tbl << "\n";
    }
  catch (const toml::parse_error& err)
    {
      std::cerr << "Parsing failed:\n" << err << "\n";
      return 1;
    }

  map<string, TrackerConf> trackerdb;
  auto tellerarr = conftbl.as_table();
  for(const auto& t : *tellerarr) {
    auto& entry = trackerdb[(string)t.first];
    entry.balance =     conftbl[t.first]["balance"].value_or(0.5);
    entry.freq =     conftbl[t.first]["freq"].value_or(500);
    cout <<"Want to play sound for tracker "<<t.first<<", balance= "<<entry.balance<<" frequency = "<<entry.freq<<endl;
        
  }
  
  LPMWrapper trackspos, tracksneg;

  auto tarr = trackertbl.as_table();
  for(const auto& t : *tarr) {
    cout<<"Defining tracker "<<t.first<<endl;
    if(trackerdb.count((string)t.first)==0) {
      cout<<"Skipping tracker "<<t.first<<", user doesn't want it"<<endl;
      continue;
    }
    auto trackerptr = &trackerdb[(string)t.first];
    auto track = trackertbl[t.first]["positive"].as_array();

    if(track) {
      track->for_each([&trackspos, &trackerptr](auto&& el) {
        if constexpr (toml::is_string<decltype(el)>) {
          trackspos.insert(*el, (void*)trackerptr);
        }
        
      });
    }
    else {
      cout<<"Not array?"<<endl;
    }
    
    track = trackertbl[t.first]["negative"].as_array();
    if(track) {
      track->for_each([&tracksneg, &trackerptr](auto&& el) {
        if constexpr (toml::is_string<decltype(el)>) {
          tracksneg.insert(*el, (void*)trackerptr);
        }
        
      });
    }
    else {
      cout<<"Negative "<<t.first<<" not array?"<<endl;
    }
  }
  
  
  for(const auto& t : trackerdb) {
    std::thread athread(playerThread, &t.second);
    athread.detach();
  }
  string line;
  while(getline(cin, line)) {

    /*
      22:42:25.323984 IP 13.81.0.219.29601 > 10.0.0.3.32902: tcp 1186
      22:42:25.323997 IP 10.0.0.3.32902 > 13.81.0.219.29601: tcp 0
      22:42:25.327216 b0:95:75:c3:68:92 > ff:ff:ff:ff:ff:ff, RRCP-0x25 query

      16:53:11.082416 IP6 2603:8000:ae00:d301:5636:9bff:fe27:6af6.59394 > 2001:41f0:782d:1::2.29603: tcp 0

    */
    if(line.find(" IP6 ") != string::npos) {
      auto pos = line.find('>');
      if(pos == string::npos)
        continue;
      auto pos2 = line.find('.', pos);
      if(pos2 == string::npos) continue;
      line.resize(pos2);
      string ip = line.substr(pos+2, pos2 - pos - 2);

      if(tracksneg.lookup(&line.at(pos+2))) {
        cout<<ip<<" negative match"<<endl;
      }
      else if(auto fptr = trackspos.lookup(&line.at(pos+2))) {
        cout<<ip<<" match!"<<endl;
        ((TrackerConf*)fptr)->counter++;
      }
    }
    else { 
      auto pos = line.find('>');
      if(pos == string::npos)
        continue;
      
      auto pos2 = line.find('.', pos);
      if(pos2 == string::npos) continue;
      pos2 = line.find('.', pos2+1);
      if(pos2 == string::npos) continue;
      pos2 = line.find('.', pos2+1);
      if(pos2 == string::npos) continue;
      pos2 = line.find_first_of(".:", pos2+1);
      if(pos2 == string::npos) continue;
      
      line.resize(pos2);
      string ip=line.substr(pos+2, pos2 - pos - 2);
      //    cout<<&line.at(pos+2)<<endl;
      if(tracksneg.lookup(&line.at(pos+2))) {
        cout<<ip<<" negative match"<<endl;
      }
      else if(auto fptr = trackspos.lookup(&line.at(pos+2))) {
        cout<<ip<<" match!"<<endl;
        ((TrackerConf*)fptr)->counter++;
      }
    }

  }
  sleep(1);
}
