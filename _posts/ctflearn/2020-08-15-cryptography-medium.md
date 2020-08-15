---
layout: post
permalink: /posts/ctflearn/cryptography-medium
title: "CTFLearn write-up: Cryptography (Medium)"
date: 2020-08-15 20:58
tags: ctflearn CTF cryptography
description: "Greetings and good ay, welcome to another ctflearn walkthrough. Today, we are going to complete the medium level crypto challenge."
---

Greetings and good ay, welcome to another ctflearn walkthrough. Today, we are going to complete the medium level crypto challenge. Let's get started.

## 1) RSA Noob

[Link: https://ctflearn.com/challenge/120](https://ctflearn.com/challenge/120)

There is a good source of RSA encryption and decryption on this [Wiki](https://en.wikipedia.org/wiki/RSA_(cryptosystem)). be sure to check on that. The downloaded information is as follows.

```
e: 1
c: 9327565722767258308650643213344542404592011161659991421
n: 245841236512478852752909734912575581815967630033049838269083
```

By referring to the RSA Wiki, we only have the public key parameter (e and n) and we do not have the d value.

```
c = m^e mod n
```

Since e is 1, it makes things easier. The possible plaintext is c, c+n, c+2n..... etc. By doing a wild guess, let's assume m = c. Converting the c decimal to hex and then ASCII, we got the following result.

![RSA flag](/assets/images/ctflearn/2020-08-15-cryptography-medium/1.png)


## 2) ALEXCTF CR2: Many time secrets

[Link: https://ctflearn.com/challenge/177](https://ctflearn.com/challenge/177)

This is one of the toughest challenges I ever face. The ciphertext is encrypted with a one-time pad (OTP) that is uncrackable or does it? There is a way to crack the OTP if the user repeating the private key. From the ciphertext below

```
0529242a631234122d2b36697f13272c207f2021283a6b0c7908
2f28202a302029142c653f3c7f2a2636273e3f2d653e25217908
322921780c3a235b3c2c3f207f372e21733a3a2b37263b313012
2f6c363b2b312b1e64651b6537222e37377f2020242b6b2c2d5d
283f652c2b31661426292b653a292c372a2f20212a316b283c09
29232178373c270f682c216532263b2d3632353c2c3c2a293504
613c37373531285b3c2a72273a67212a277f373a243c20203d5d
243a202a633d205b3c2d3765342236653a2c7423202f3f652a18
2239373d6f740a1e3c651f207f2c212a247f3d2e65262430791c
263e203d63232f0f20653f207f332065262c3168313722367918
2f2f372133202f142665212637222220733e383f2426386b
```

Each line of the messages is encrypted with the same private key. Full credit to this [user write up](http://dann.com.br/alexctf2k17-crypto100-many_time_secrets/) and [this script](https://github.com/Jwomers/many-time-pad-attack/blob/master/attack.py), The ciphertext can be decoded by applying the following script.

```python
#!/usr/bin/python
## OTP - Recovering the private key from a set of messages that were encrypted w/ the same private key (Many time pad attack) - crypto100-many_time_secret @ alexctf 2017
# @author intrd - http://dann.com.br/
# Original code by jwomers: https://github.com/Jwomers/many-time-pad-attack/blob/master/attack.py)

import string
import collections
import sets, sys

# 11 unknown ciphertexts (in hex format), all encrpyted with the same key
c1 = "0529242a631234122d2b36697f13272c207f2021283a6b0c7908"
c2 = "2f28202a302029142c653f3c7f2a2636273e3f2d653e25217908"
c3 = "322921780c3a235b3c2c3f207f372e21733a3a2b37263b313012"
c4 = "2f6c363b2b312b1e64651b6537222e37377f2020242b6b2c2d5d"
c5 = "283f652c2b31661426292b653a292c372a2f20212a316b283c09"
c6 = "29232178373c270f682c216532263b2d3632353c2c3c2a293504"
c7 = "613c37373531285b3c2a72273a67212a277f373a243c20203d5d"
c8 = "243a202a633d205b3c2d3765342236653a2c7423202f3f652a18"
c9 = "2239373d6f740a1e3c651f207f2c212a247f3d2e65262430791c"
c10 = "263e203d63232f0f20653f207f332065262c3168313722367918"
c11 = "2f2f372133202f142665212637222220733e383f2426386b"
ciphers = [c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11]
# The target ciphertext we want to crack
target_cipher = "2239373d6f740a1e3c651f207f2c212a247f3d2e65262430791c"

# XORs two string
def strxor(a, b):     # xor two strings (trims the longer input)
    return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b)])

# To store the final key
final_key = [None]*150
# To store the positions we know are broken
known_key_positions = set()

# For each ciphertext
for current_index, ciphertext in enumerate(ciphers):
	counter = collections.Counter()
	# for each other ciphertext
	for index, ciphertext2 in enumerate(ciphers):
		if current_index != index: # don't xor a ciphertext with itself
			for indexOfChar, char in enumerate(strxor(ciphertext.decode('hex'), ciphertext2.decode('hex'))): # Xor the two ciphertexts
				# If a character in the xored result is a alphanumeric character, it means there was probably a space character in one of the plaintexts (we don't know which one)
				if char in string.printable and char.isalpha(): counter[indexOfChar] += 1 # Increment the counter at this index
	knownSpaceIndexes = []

	# Loop through all positions where a space character was possible in the current_index cipher
	for ind, val in counter.items():
		# If a space was found at least 7 times at this index out of the 9 possible XORS, then the space character was likely from the current_index cipher!
		if val >= 7: knownSpaceIndexes.append(ind)
	#print knownSpaceIndexes # Shows all the positions where we now know the key!

	# Now Xor the current_index with spaces, and at the knownSpaceIndexes positions we get the key back!
	xor_with_spaces = strxor(ciphertext.decode('hex'),' '*150)
	for index in knownSpaceIndexes:
		# Store the key's value at the correct position
		final_key[index] = xor_with_spaces[index].encode('hex')
		# Record that we known the key at this position
		known_key_positions.add(index)

# Construct a hex key from the currently known key, adding in '00' hex chars where we do not know (to make a complete hex string)
final_key_hex = ''.join([val if val is not None else '00' for val in final_key])
# Xor the currently known key with the target cipher
output = strxor(target_cipher.decode('hex'),final_key_hex.decode('hex'))

print "Fix this sentence:"
print ''.join([char if index in known_key_positions else '*' for index, char in enumerate(output)])+"\n"

# WAIT.. MANUAL STEP HERE
# This output are printing a * if that character is not known yet
# fix the missing characters like this: "Let*M**k*ow if *o{*a" = "cure, Let Me know if you a"
# if is too hard, change the target_cipher to another one and try again
# and we have our key to fix the entire text!

#sys.exit(0) #comment and continue if u got a good key

target_plaintext = "cure, Let Me know if you a"
print "Fixed:"
print target_plaintext+"\n"

key = strxor(target_cipher.decode('hex'),target_plaintext)

print "Decrypted msg:"
for cipher in ciphers:
	print strxor(cipher.decode('hex'),key)

print "\nPrivate key recovered: "+key+"\n"
```

![alaxander flag](/assets/images/ctflearn/2020-08-15-cryptography-medium/2.png)

## 3) Substitution Cipher

[Link: https://ctflearn.com/challenge/238](https://ctflearn.com/challenge/238)

This task requires your dedication to finding the [right character](https://crypto.interactive-maths.com/frequency-analysis-breaking-the-code.html) and substitute it. I prefer to kick start the substitution on the of November and December.

![november](/assets/images/ctflearn/2020-08-15-cryptography-medium/3.png)

![december](/assets/images/ctflearn/2020-08-15-cryptography-medium/4.png)

Play around with the substitution, you will come across with the following combination.

![substitute](/assets/images/ctflearn/2020-08-15-cryptography-medium/5.png)

![sub flag](/assets/images/ctflearn/2020-08-15-cryptography-medium/6.png)

## 4) 5x5 Crypto

[Link: https://ctflearn.com/challenge/263](https://ctflearn.com/challenge/263)

First of all, you need to create a 5x5 letter matrix without the k.

![5x5 flag](/assets/images/ctflearn/2020-08-15-cryptography-medium/7.png)

By looking at this combination  1-3,4-4,2-1,{,4-4,2-3,4-5,3-2,1-2,4-3,_,4-5,3-5,} , e.g 1-3 represent row 1 column 3 which is C. Keep tracking the combination, you will find the answer.

## Conclusion

That's all for the crypto medium level from the ctflearn. Until next time ;)
