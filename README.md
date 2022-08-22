# googerteller

Audible feedback on just how much your browsing feeds into Google.

By bert@hubertnet.nl / https://berthub.eu/

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

Replace `192.0.2.1` with the IP address of your default gateway (e.g. your Internet router).

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
