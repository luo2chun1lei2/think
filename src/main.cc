#include "object.h"

#include <stdio.h>

/**
 zhang		// 缺省的设定了名字。
 	age:43
 > // 或者 zhang.age = 43
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
 > // 是不是也可以这样设定 zhang.teach = wang，这个对应简单的from/to类型关系
 > zhang teach ?
 > print ? 				// 应该显示两个人，li和张
 */
/**
 a.prop = b		// a的属性prop是b对象。
 属性是否表示动作？还是只是表述所属关系？SQL语句牵连的Table，只是用来表述关系用的。
 实际上我想表述的是关系，是对象和对象之间的联系，而不是动作之类的。
 Table之类的构筑的是数据之间的关系，通过关键字连接，但是数据之间的关系不容易组合，
 所以这里重点是关系，关系的组合等是重点。
 动作不是关系，动作是建立关系和维护关系用的。
 属性和动作是关系的下一层。
 1. 最简单的关系是两个对象之间的联系，这种联系可以赋予任何的含义，但是并不在数据表格之中规定。
 2. 把这些简单的关系，通过关系之间的关系，组合起来，形成复杂的关系。
 3. 所有的对象变成简单的属性模型，其实和Table本质上一样的。
 4. 然后
 */
 /**
  另外一个想法：
  1，关系是描述对象和对象之间的关系。
  2，对象代表所有的元素。
  3，比如 文件是一个对象，它有名字，有大小，有访问权限，有内容。
  4，“有”就是一个关系，所以“文件有名字”，实际上是“此文件和此名字之间具有‘起名’关系”。
  5，此目录包含此文件，是目录和文件之间有“包含”关系。
  6，如果把关系简单化为属性，那么就无法把关系独立出去，也就失去了组合关系之类的功能。
  a.p = b --> r<a, b>
  以后还可以扩展 r<a, b, ...>，但是<a,b, ...>是无法代表r的。
  a.r表示a的r关系，注意关系是具有方向性的。
  r<from=a, to=b>，是不是感觉有点像“函数”，和函数的区别是，关系是建立后，一直维持的，
  函数只是动作，并不是固定的。
  关系靠着“映射”来维持关系，“映射”是最简单的关系。
  
  obj
  	.name = "zhang"	// Own("name", from=obj, to=value("zhang"))
  	.age = 41
  	.sex = female
  obj
  	.name = "li"
  	.age = 11
  	.set = male
  teach(from=obj[name=zhang], to=obj[name=li])
  每个对象都有一个名字，这个如果也是关系设定化，就有一个先有鸡，还是先有蛋的问题，
  所以就设定每个对象都有一个接口是get_name和set_name，唯一性由上层模块保证。
  每个联系都是关系，包括属性（比如：名字）都是关系，只会造成关系递归，无法形成真正的关系。
  
  不如在底层真的加入一个属性层，property=<key, rel>，key是自定义的名字，这个属性和之前讨论的不一样，
  是有限的，写死的函数。
  get/set name, get/set from, get/set to.
  obj.set_name("zhang")
  rel.set_from("age", obj)
  rel.set_to("assigned", 41)
  
  rel.set_from("teach", obj1)
  rel.set_to("taugh", obj2)
  
  不仅仅限于"from"和"to"的关系怎么办？
  */
/**
 总结之前的想法，对象和对象之间用关系联系，而关系也是对象。
 比如：老师教学生。老师是一个对象，学生是一个对象，而“教”则是关系，连接上面两个对象。
 老师具有的信息，比如姓名、年龄等，可以描述为：老师具有年龄。
 
 Teacher has name, age.
 
 obj1.type = Teacher
 obj1.name = "zhang"
 obj1.age = 45

 Student has name, age.
 
 obj2.type = Student 
 obj2.name = "li"
 obj2.age = 11
 不要把类型和具体对象混淆，类型“老师具有年龄这个对象”，而类型的具体实例则是“张老师的年龄是45”。
 
 Teach has from, to.
 t1.type = Teach
 t1.from = obj1
 t1.to = obj2
 
 t1.teach.to is obj2.
 
 1. 如果教多个对象怎么办？
 2. 关系如何组合？以及对象如何组合？
 3. 关系如何维护？
 4. 动作又如何运转？
 */
void test_1()
{
	TObject obj1;
	
	// obj.name = "zhang"
	TRelOwn rel("name");
	rel.set_rel(""obj1);
	rel.set_to(TString("zhang"));
	
	// obj.age = 43
	obj1.set_rel("age", 43);
	
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
