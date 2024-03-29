# Elliptic-Curve
#### 	用C++对有限域椭圆曲线加密算法复现，包括利用一些数学定理如扩展欧几里得构建一个循环群，再利用循环群特点实现对信息加密解密，并结合哈希实现对信息的签名和验证。
	运用到的C++技术：运算符重载、构造、拷贝构造和赋值、结构体、类、STL等

用C++实现一个简单的实例：A向B发送信息的加解密，签名和验证

通过有限域椭圆曲线构建一个循环群，利用椭圆曲线的离散对数问题实现对信息加解密，原理和实现参考链接：https://www.bilibili.com/video/BV1PP4y1M7Vk?spm_id_from=333.999.list.card_archive.click&vd_source=3535ff42ad6e2406310b6933e4f8b75e

签名和验证：

![图片1](./image/图片1.png)

![图片2](./image/图片2.png)

代码运行：

![image-20220906134358452](./image/image-20220906134358452.png)

![image-20220906134534351](./image/image-20220906134534351.png)

A利用B的公钥对明文加密发送给B,

B拿到密文后用B自己的私钥解密得到A发来的明文

![image-20220906134856399](./image/image-20220906134856399.png)

![image-20220906141008719](image/image-20220906141008719.png)

![image-20220906140830084](./image/image-20220906140830084.png)

对上面两条信息签名和验证：

A先对明文哈希，然后用自己的私钥对得到的哈希签名，把签名后的信息和A的公钥一起发送给B

B对密文解密得到明文，用A的公钥对明文验证，如果和A签名后的信息一样则返回1，否则返回0
