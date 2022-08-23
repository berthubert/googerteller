# googerteller

Audible feedback on just how much your browsing feeds into Google.

By bert@hubertnet.nl / https://berthub.eu/

Makes a little bit of noise any time your computer sends a packet to a
Google service, which excludes Google Cloud users.

Demo video [in this tweet](https://twitter.com/bert_hu_bert/status/1561466204602220544)

## How to compile

You need a C++ compiler like `gcc-c++` and CMake for compiling the binary.

You also need to install `libpcaudio` (`libpcaudio-dev` on Debian/Ubuntu, `pcaudiolib-devel` on Fedora/Red Hat, `pcaudiolib` in Arch Linux).

Then run:

```bash
cmake .
make
```

## How to run

```bash
sudo tcpdump -n -l dst net 192.0.2.1/32 $(for a in $(cat goog-prefixes.txt); do echo or dst net $a; done)  |  ./teller 
```

And then cry.

### Arch Linux

googerteller is available as a package in the Arch User Repository (AUR), you can install and run with the following commands:

```bash
git clone ssh://aur@aur.archlinux.org/googerteller-git.git
cd googerteller-git
makepkg -si
googerteller
```

## Problems

If `tcpdump` complains about `Warning: Kernel filter failed: Cannot allocate memory`, try
this first:

```bash
sudo sysctl net.core.optmem_max=204800
```

## Data source

The list of Google services IP addresses can be found on [this Google
support page](https://support.google.com/a/answer/10026322?hl=en).

Note that this splits out Google services and Google cloud user IP
addresses.
