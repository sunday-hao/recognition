# recognition
#figure_recognition.cpp 用来识别多边形形状与个数。
#在文件的第121行通过imread传入图片

#cpp文件里定义了两个类low,high
#每个类里各有一个成员函数transformer，分别是对低级，中高级图片的预处理方法

#接下来定义一个函数recognition，传入img和clo两个Mat类型的参数，其中img是你想要识别的图片（一般是经过预处理的图片），clo是识别后传出的图片。

代码思路：
low类的transformer函数，先将成员变量low_img用cvtColor换成灰度图，再使用全局二值化（THRESH_OTSU）

high类的transformer函数，先将转换为HSV颜色空间，再读取图片像素点的HSV各值，得到inRange函数所需的阈值，然后根据此阈值得到mask
再做开运算消除残留噪音

recognition函数，使用findocntours和approxPolyDP并且面积筛选轮廓得到多边形轮廓，用相应api将方框画在克隆图片上

补充：本来还有一个middle类，后来发现high类对中级图片效果更好，于是删除了middle类
     如有误差，请调节相关阈值
