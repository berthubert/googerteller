# googerteller
audible feedback on just how much your browsing feeds into google

By bert@hubertnet.nl / https://berthub.eu/

## How to compile
First install libpcaudio, then:

```
cmake .
make
```

## How to run:

```
sudo tcpdump -n -l dst net 192.0.2.1/32 $(for a in $(cat goog-prefixes.txt); do echo or dst net $a; done)  |  ./teller 
```

And then cry.

## Data source
The list of Google services IP addresses can be found on [this Google
support page](https://support.google.com/a/answer/10026322?hl=en).

Note that this splits out Google services and Google cloud user IP
addresses.
