#!/bin/sh

ipset create google-services hash:net
for a in $(cat goog-cloud-prefixes.txt)
do 
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
iptables -I OUTPUT -m set --match-set google-services dst -j NFLOG --nflog-group 20 
ip6tables -I OUTPUT -m set --match-set google-services6 dst -j NFLOG --nflog-group 20 

