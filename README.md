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
Google is so large its IPv4 and IPv6 footprint can't be handled by tcpdump,
or at least not efficiently. Therefore we need to define an ip(6)tables
`ipset`. This will first exclude Google Cloud, and then include all the
other Google IP addresses.

Install iptables 'ipset', and run (as root) the `ipset-setup.sh` script, or
execute:

```
ipset create google-services hash:net
for a in $(cat goog-cloud-prefixes.txt)
do 
echo $a
	ipset add google-services $a nomatch
done 
for a in $(cat goog-prefixes.txt)
do 
	ipset add google-services $a
done

ipset create google-services6 hash:net family inet6
for a in $(cat goog-cloud-prefixes6.txt)
do 
	ipset add google-services6 $a nomatch
done 

for a in $(cat goog-prefixes6.txt)
do 
	ipset add google-services6 $a
done
iptables -I OUTPUT -m set --match-set google-services dst -j NFLOG --nflog-group 20 --nflog-threshold 1
ip6tables -I OUTPUT -m set --match-set google-services6 dst -j NFLOG --nflog-group 20 --nflog-threshold 1
```

Then start as:
```
sudo tcpdump -i nflog:20 -ln | ./teller
```
And cry.

## Data source
The list of Google services IP addresses can be found on [this Google
support page](https://support.google.com/a/answer/10026322?hl=en).

Note that this splits out Google services and Google cloud user IP
addresses. However, it appears the Google services set includes the cloud IP
addresses, so you must check both sets before determining something is in
fact a Google service and not a Google customer.
