# Look-Up Table Masking

This is my implementation of the look-up masking algorithm described in ["Higher Order Masking of Look-Up Tables"](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.400.5094&rep=rep1&type=pdf) by Jean-Śebastien Coron.

# Results

Power-analysis of an AES SBox lookup on an ATXMega128 using ChipWhisperer. The plots show a correlation attack with 200 collected power traces. 

Here, the SBox lookup was performed without any masking. The correct key can be clearly seen from the plot, as the power model has a very high correlation with the real power consumption for the correct key. 
![No masking](https://github.com/misc0110/lut-masking/raw/master/plots/no_mask.png "No masking")

The next plot shows the correlation after masking the SBox lookup with the masking algorithm. For the same number of traces, there is no correlation and the correct key cannot be recovered. 
![Masking](https://github.com/misc0110/lut-masking/raw/master/plots/mask.png "With masking")


