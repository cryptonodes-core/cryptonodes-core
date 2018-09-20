#!/usr/bin/python
# Copyright 2014 BitPay, Inc.
# Copyright 2018-2019 Cryptonodes Core developers.
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
import bctest
import buildenv

if __name__ == '__main__':
	bctest.bctester(os.environ["srcdir"] + "/test/data",
			"bitcoin-util-test.json",buildenv)

