#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <pcaudiolib/audio.h>

using namespace std;

int main()
{
  audio_object* ao;

  ao=create_audio_device_object(0, "teller", "");
  if(!ao) {
    cerr<<"Unable to open audio file "<<endl;
    return 0;
  }
  
  int res = audio_object_open(ao, AUDIO_OBJECT_FORMAT_S16LE, 44100, 1);
  if(res < 0) {
    cerr<<"Error opening audio: "<<audio_object_strerror(ao, res)<<endl;
  }

  std::atomic<int64_t> counter = 0;
  auto player = [&]() {
    vector<int16_t> data;
    int ourcounter=0;
    data.reserve(44100);
    while(counter >= 0) {
      data.clear();
      if(ourcounter < counter) {
        for(int n=0; n < 250; ++n) {
          int16_t val = 20000 * sin((n/44100.0) * 500 * 2 * M_PI);
          data.push_back(val);
        }
        ourcounter++;
        if(counter - ourcounter > 1000)
          ourcounter = counter;
      }
      else {
        for(int n=0; n < 150; ++n) {
          data.push_back(0);
        }
      }
      
      audio_object_write(ao, &data[0], data.size() * sizeof(decltype(data)::value_type));
      // audio_object_flush(ao);
    }
  };

  std::thread athread(player);
  string line;
  while(getline(cin, line)) {
    counter++;
  }
  counter = -1;
  athread.join();
  sleep(1);
}
