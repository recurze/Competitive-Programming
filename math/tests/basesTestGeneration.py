#!/usr/bin/env python
# -*- coding: utf-8 -*-
# File              : basesTestGeneration.py
# Author            : recurze
# Date              : 16:34 25.12.2018
# Last Modified Date: 17:02 25.12.2018

from random import randint as ri
c = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
for i in xrange(2, 37):
    for _ in xrange(10000):
        s = '0'
        while int(s, i) < 10**8:
            s += c[:i][ri(0, i-1)]
        print s[:-1].lstrip('0')
