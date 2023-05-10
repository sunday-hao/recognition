# recognition
#figure_recognition.cpp 用来识别多边形形状与个数。
#在文件的第134行通过imread传入图片
#cpp文件里定义了三个类low,mid,high
#每个类里各有一个成员函数transformer，分别是对低级，中级，高级图片的预处理方法
#接下来定义一个函数recognition，传入img和clo两个Mat类型的参数，其中img是你想要识别的图片（一般是经过预处理的图片），clo是识别后传出的图片。

