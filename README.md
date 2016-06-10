# Look-Up Table Masking

This is my implementation of the look-up masking algorithm described in ["Higher Order Masking of Look-Up Tables"](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.400.5094&rep=rep1&type=pdf) by Jean-Śebastien Coron.

# Results

Power-analysis of an AES SBox lookup on an ATXMega128 using ChipWhisperer. The plots show a correlation attack with 200 collected power traces. 


![No masking](https://github.com/misc0110/lut-masking/raw/master/plots/no_mask.png "No masking")

![Masking](https://github.com/misc0110/lut-masking/raw/master/plots/no_mask.png "No masking")


