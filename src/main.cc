#include "object.h"

#include <stdio.h>

/**
 zhang		// 缺省的设定了名字。
 	age:43
 li			
 	age:11
 teach
 	from:@zhang	// @ 开头的表示一个已知的对象
 	to:@li
 	
 > print zhang.age
 > zhang teach ? 		// zhang 教了谁？
 > print ? 				// 打印这个谁
 > ? teach li
 > print ?
 > zhang ? li
 > print ?
 > wang.age = 12		// 建立了一个对象，名字是 wang
 > zhang teach wang		// 建立关系：张教了王，左边缺省是from，右边缺省是to
 // 以后的语法可以 A do B by C with D --> do.from = A, .to=B, .by=C, .with=D.
 > zhang teach ?
 > print ? 				// 应该显示两个人，li和张
 */
void test_1()
{
	TObject zhang;
	zhang.set_property("name", "张");
	zhang.set_property("age", 43);
	
	TObject li;
	li.set_property("name", "li");
	li.set_property("age",  11);
	
	TRelation teach;
	teach.set_property("name", "teach");
	
	zhang.set_property(&teach);
	teach.set_property("from", &zhang);
	teach.set_property("to", &li);
} 
   
int main(int argc, char * argv[])
{
	test_1();
	return 0;
}
