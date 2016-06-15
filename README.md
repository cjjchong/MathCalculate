# MathCalculate

Description : read FILE1 ,calulate then save result into FILE2
 
 FILE1 
 f1  X10 X11 X12 X13 .....
 f2  X20 X21 X22 X23 .....
 f3 ....
 ......
 
 FILE2
 f1 result1
 f2 result2
 f3 result3
 ......
 
 Formula
 
 result = sqrt( sum( square ( Xij*2*PI*fi) )   / countOf(Xij) )