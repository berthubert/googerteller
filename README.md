# googerteller
audible feedback on just how much your browsing feeds into google

## How to compile
First install libpcaudio, then:

```
cmake .
make
```

## How to run:

```
sudo tcpdump -n -l dst net 1.2.3.4/32 $(for a in $(jq .prefixes < goog.json  | grep ipv4Prefix | cut -f2 -d: | sed s/\"//g); do echo or dst net $a; done)  |  ./teller 
```

And then cry.
