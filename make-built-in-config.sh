#!/bin/sh
cd $1
(
echo \#pragma once
echo 'constexpr char tellertoml[]=R"('
cat teller.conf 
echo ')";'

echo 'constexpr char trackerstoml[]=R"('
cat trackers.conf 
echo ')";'
) > configs.hh