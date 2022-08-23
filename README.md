# googerteller

Audible feedback on just how much your browsing feeds into Google.

By bert@hubertnet.nl / https://berthub.eu/

Makes a little bit of noise any time your computer sends a packet to a
Google service, which excludes Google Cloud users.

Demo video [in this tweet](https://twitter.com/bert_hu_bert/status/1561466204602220544)

## How to compile

You need a C++ compiler like `gcc-c++` and CMake for compiling the binary.

You also need to install `libpcaudio` (`libpcaudio-dev` on Debian/Ubuntu, `pcaudiolib-devel` on Fedora/Red Hat).

Then run:

```
cmake .
make
```

## How to run

```
sudo tcpdump -n -l dst net 192.0.2.1/32 $(for a in $(cat goog-prefixes.txt); do echo or dst net $a; done)  |  ./teller 
```

And then cry.

## Problems

If `tcpdump` complains about `Warning: Kernel filter failed: Cannot allocate memory`, try
this first:

```
sudo sysctl net.core.optmem_max=204800
```

## Data source

The list of Google services IP addresses can be found on [this Google
support page](https://support.google.com/a/answer/10026322?hl=en).

Note that this splits out Google services and Google cloud user IP
addresses.

## Macos
You will need to install the pcaudio library:
  https://github.com/espeak-ng/pcaudiolib#mac-os
In turn this needs automake installed (from xcode or brew). With that it is standard install
WIth libpcaudio in place, follow instructions above.