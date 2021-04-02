# 思考

【满足要求的最简洁的实现，才是最好的实现。】

## 目的
研发一种工具，可以辅助思考。

我们在思考问题的时候，大部分集中在三个方面：观察、分析和影响。
观察是研究事物的表现，不过随着分析和影响的深入，会重新观察目标，甚至观察其他的目标。
分析是在观察的结果上，用科学的方法去归纳和解释事物的运行的规律，当然这些规律可能只是其中的一种解释，甚至可能是错误的，只要部分符合就行了。
最后是影响，大部分情况下分析得到的规律会有很多，那么仅仅是隔离在研究目标之外，是很难搞明白到底哪种规律才是正确的，
何况有些情况下，观察者（我们）也处于和研究目标在一起的情况。所以需要在规划好的影响下，重新进行观察和分析，得到更加准确的规律。

本软件重点在分析，它通过**描述目标的关系**，形成“事物之间的关联”。因为分析本身必须符合逻辑规则，
所以针对关联可以进行分析，而且可以提高观察者的分析能力。

目前使用的程序，是建立“函数”(function)为基础的软件系统，而函数体现的是“动作”。
这些函数会根据输入改变或查询系统各个部分的状态，要求是无论怎么改变后都需要保持系统的各个部分状态的一致性。
它们的流程是，当“触发”(Trigger)被引发后，一个一个函数调用起来，改变系统的各个部分，直到相关动作完成。

我考虑的这个系统在现有系统中需要提高一步，参考prolog语言的做法：
	1. 系统的核心是关系（Relation），而不是函数，函数是用于建立、删除、修改“关系”。
		关系是**描述**语句，描述系统内对象之间的关系。
	2. 建立后的关系系统，根据关系可以进行查询、判断和分析。这些是当前语言系统不足的，当前系统只能看到动作，
		但是状态中间的关系是隐含的，需要用户自己在思想中建立。
	3. 关系不仅仅可以用来建立系统的某个状态内的各个部分之间的关系，实际上也可以建立不同状态之间的关系，只要是研究的目标就行。
		另外，将**推理**方法用于关系分析时，能够得到更多的关系，虽然本质上知识的总量并没有变化。
		而且关系中的某些条件符合时，也可能引发设定动作的运行，建立新的关系。
		动作 -> 关系 -> 动作 -> 关系 ...
	4. 系统在定好的关系中，也可以按照关系进行运行，这就能够将此系统应用在实际的项目中。
		比如 `map(from=data, to=display)`，这样如果实现了`map`后，那么当data改变后，就会改变display了。
## 需求汇总的基本想法
1. 增删改查关系。【这是核心数据结构】
2. 根据关联关系，可以得到更多的关联信息，比如衍生关系、组合关系，以及约束关系等。【下面是关系的一些情况，不是动作】
	1. 衍生：通过推理，得到其他的关系(a->b->c := a->c)。或者在某些附加关系下，推导系统中关系情况。(if a==0 := c=b)
	2. 组合：多个关系的组合下，形成新的关系名称。 r1(a, b) & r2(b, c)  则 r3(a, c)。【类似类型】
	3. 约束：检查一组对象是否符合关系要求。【类似接口，不过是有检查功能的】
3. 可以按照关联关系进行系统运行。

## 设计
因为这个是尝试性的软件，所以主体采用循序渐进的开发方法，每一步都要简单、可以测试、有一定的实用行。
下面是从不同的方面来总结软件的功能都有哪些，按照从简单到复杂的方向添加。后面会根据这些功能进行组合成工程进度安排。

功能的多个层次：
第一层关系的数据结构建立，然后应用查询之类的，
第二层则是可以扩展关系的描述，让关系可以描述真实的系统。
第三层根据关系来运行系统，这个就可以应用到真实系统中了。

设计分成三个部分：
第一部分是作为最核心的数据结构和增删改查接口。
第二部分是数据结构外层的容器和应用接口，比如输入、输出模块，还有外部的语言，可以不止一个。
第三部分是扩展部分，仿效libc库和Java的类库。

### 数据结构设计

#### 元素+关系

1. 元素(Element)是所有对象的基类。
	有一个id，在全局表示唯一。【需要吗？全局唯一是为了什么？定位？全局的Tree结构不行吗？】
	有一个name。【一个元素的关系可以在元素的范围内重名，比如我的朋友可以是多个，也可以单列，这个问题怎么办？属于R的重名】
	特化的元素：
		1. 值类型，内部是一个值，比如字符串、整数、浮点数、布尔值等。主要用于计算和文字处理。
			【计算或文字处理，需要一个共通的接口，就是value、string！】
			是否可以认为所有的元素都可以获取值（是字符串），然后再根据公式强制转化为数字之类的。
		2. 关系，指明多个元素之间的关系。
	比如:
	```python
	// e0是程序内的名字，后面是此元素的具体属性。
	// 具体属性是值: e0 的年龄是43。
	e0 = People(xingming="luocl", old=43, sex="male")
	```

	一个元素可以拥有任意的属性(property)，这些property都有值，值可以是任意的元素。
	属性(property)或者标签(tag)都相当于一个 a--r-->b 的关联。
	比如说 a的属性r，那么就是说 “a的关系b对应的元素”，这里就是b了。

2. 元素延伸出关系(Relation)，关系可以关联多个元素。一个元素可以通过关系关联多个对象。一个元素可以有多个关系。
	【关系的名字（不是类型）必须是唯一的？那么就需要R必须有一对多的实现。】
	a--r-->b : a和b之间有关系r，a的r是b（这种称为关系的属性描述方法）。
	```python
	// 可以设置e0和e1的关系为r1，e0和e2的关系也为r1
	// 等号的右边是自变量，左边是随便量，就是当自变量发生变化后，随便量需要跟着变化。反向则不同。
	e0.r1 = e1, e2， ...
	```
	等同于
	```python
	// 【怎么知道是relation还是普通element，或者是不需要区分？】
	r1(e0, e1)
	r1(e0, e2)
	...
	```
	现实中的例子：
	```
	我.侄子 = 小多, 小豹
	```
	【下面的想法，有待再确认和修改】
	* e0可以是表达式，只要最后的结果是一个必须已存在的元素。
	* r1可以是表达式，最后的结果只要是一个“文字”，这样就可以创建一个新的relation。
	* e1/e2可以是表达式，如果结果是一个必须已经存在的元素，那么就设置到r1中。如果结果是一个值，那么就创建一个新的元素。
	* 关系是有方向的，可以单向或者双向的。比如 我和小多是亲戚，“亲戚”就是一个双向的关系。

#### 衍生关系 【这里应该是衍生、组合和约束等 TODO 没有写】

在逻辑判断中，会出现“如果……就……“的逻辑，那么需要这样定义
```python
	sum= { 1 if a==b; sum=a/(a-b) else };
```

```python
	sum= { if n > 100 in n : Numbers }; # 数字中，大于100的。
```

上面的关系是在条件的基础上建立的，所以是“衍生”的关系。
和之上的关系不同的是，以上的关系都会记录在关系中，之后都会对系统产生影响。

### 应用设计

外部模块设计，分成应用、输入、输出、控制等，但是最难也是最重要的是**语言设计**。
下面将通过逐步的步骤来实现当前的系统的“语言”级别描述方法。

注意，语言设计到两个部分，第一个是描述关系，第二部分是建立、修改、删除、查询关系的动作，
这两部分要明确，动作在这里也非常重要，因为关系必须建立才能有。

#### 动作+函数
为了建立关系模型，需要有“动作”，动作就是描述“干什么”，这样就可以搭建一个关系模型。
和其他程序的区别就是：动作建立的是关系，不是只设定最终的结果，
比如:
```python
s = a+b+c
```
一般的程序是将三个数字的和赋值给s，之后s和a、b、c之间的关系就无法看到了，除非看到代码。
而此语言则是保留`s=a+b+c`之间的关系，之后等到a/b/c发生变化时，s会跟着计算。

1. 单个动作:
```python
r = R(x=1, y=2, z=3)	# 建立
r.x = 100		# 修改
delete(r.y)		# 删除
ask(r.z)		# 查询
```
通过类型来新建一个元素，或者就是一个动作。【这里假定动作就是一个“建立元素”，不知道是否可以？】

2. 表达式
多个元素和关系可以形成一个组合元素(combined element)，此组合元素对外的关系就是内部所有元素对外关系。
当然，多个关系也可以组合成一个关系(combined relation=combined element)。
可以将关系和元素组成一个有意义的组合，形成一个“组合对象“，这个就是表达式。

表达式是各种元素的有效组合，可以是(等号右边的)
```python
	expr = a
	expr = a.b
	expr = (a + 3) / 2
	expr = (a.b + 3) / 2
```

还有分支和循环逻辑语句
```python
	if (a == b) {
		sum = NAN;
	} else {
		sum = a/(a-b);
	}
	while(expr) {
		...
	}
```
这个和后面的关系中的循环逻辑和分支是不同的，因为这里的判断和循环是不保留在“关系”中的。

表达式用另外的更加通用的描述方法【不要，这样太奇怪了，还是用平常的书写方法最好。】
```python
	expr = /( +(a.b, 3), 2)
	expr = f1( f2(a, b), c) # 更加的通用！但是不符合一般写法。
```

3. 多个动作成一个函数
```python
f = Function(a, b, c) { # 定义
	a = ABC(a, b, c)
	r = R(d, e, f)
}
f(x, y, z)	# 调用
```

#### 扩展

原有的关系是无法和实际的关系一一对应的，那么扩展后的对象，如果无法复制和约束，将无法在实际的大工程中应用，
所以这里需要实现必须的扩展：自定义模板和自定义约束（或者称为接口）。

1. 模板：可以从此模板衍生其他的模板，或者元素。
	这样就不用每个对象重复设置关系，这样对于关系来说，可以设定某一类型的关系，而不再是某个具体的对象的关系。

	```python
	ABC = Relation(a, b, c)
	{
		c = a + b
	}
	abc = ABC(1, 2, sum) # 设定了 sum 和 1、2 的关系。
	```

	```python
	# 这个是新的元素，设定了一个元素。
	DEF = ABC(old, height) {
		self.old = old
		self.height = height
	}

	```python
	# 模板之间的继承
	XYZ(weight) = ABC(old, height) {
		self.weight = weight;
	}
	```

2. 接口，可以用于“检测匹配”，比如接口，凡是符合这个接口的，就都可以用。
	
	如果是接口的定义，必须从Interface继承：
	```python
		abc = Interface() {
			father; // 必须有的属性
			mother;
			r123(father, mother); 	// 必须具有的关系
		}
	```
	接口可以用于检查某个元素是否符合要求！

#### 关系模型

关系模型这里作为一个在语句、函数等之上的一个高级元素，可以提供给其他模块来使用。
和普通程序类似，此程序允许建立独立的关系模型，就相当于程序中的静态/动态模块，不同的是这里是逻辑单位，而不是编译好的实体单位。

1. 推导：从已有条件，得出一个非内在的结果，是推导条件。根据推导条件推导出需要查询的结果。【其实推导也是在建立新的关系，当条件成立的时候】
	可以参考“prolog的推理公式”，就能将逻辑组合出来：符合条件，就能达成什么情况。达成什么情况，就会出现必要条件。（充分和必要条件）

	推导描述的是`a == b`成立时，得出`c=1`，否则“c=a/(a-b)”。
	```python
	c=1 :- a==b; c=a/(a-b) :- a!=b;
	```

#### 模型之间的关系

本章描述多个模型之间的关系。
问题的提出是，因为以后开发必然需要将程序切成不同的组，这些组之间肯定也需要关联的，这个就是描述这个层次的关系的。

#### 系统设计【这部分是最难的】
	1. 创建模型，容纳元素。
	2. 针对元素的检索、管理等。
	3. 针对整个模型的静态分析。
	4. 针对模型的动态运转。比如关系描述的不再是静态的关系，而是动态的情况，那么系统就需要运转起来看看情况。
	5. 模型之间的转化，比如将模UML型转化为实际的代码，或者画面模型转化为实际的画面。

### 各部分扩展

#### 应用扩展

#### 人机接口
	1. API函数。
	2. 脚本可以调用API函数，特点是必须按照循序执行，才能得到正确的模型，所以里面有 if、for等。比如现在张三结交李四。
	   它的本质是通过执行语句，来构造出一个模型。
	   正则表达式的脚本（regrex），和高级的语法脚本（Flex+Bison）。
	3. 关系模型的描述文件。静态类型的结构描述，不是执行的，从任何顺序读取都能够恢复成正确的模型。
	   要求描述语句是静态的，而不是动态的。比如张三是李四的朋友。本质上，它就是模型，至于怎么构造，程序自动完成。
	4. 模型数据的DB数据保存，以后用于数据保存和重现。

#### 实际库扩展


## 实现和测试

#### 架构设计
	1. 可以进行单元测试。
	2. 可以单独运行。
	3. 接受简单的输入和输出。
	4. 能够有复杂的输入和输出。
	5. 支持不同模型的切换和处理。
	6. 具有图形画面。

【现在偏离了使用，目前最要紧的是制作函数调用关系，以及模块包含关系图，其他的功能如果没有用到，就先不要实现。】
逐步负责 + 可以使用

想实现的实用功能：
	1. 任务列表、说明列表等。 【简单实现】
	2. 函数、模块之间的调用关系图。 【简单的实现】
	3. 模块、包、系统之间的关联关系图，比如依赖、调用等。 【简单的实现】
	4. 查询和分析。【<-- 要实现表达式，需要重新规划整个语言语句！】
	5. 运行关系。

本软件的基本流程：
	1. 管理语句（描述语句+控制语句） -> 关系模型 -> 输出
	2. 输入 -> 处理 -> 关系模型 -> 处理 -> 新的关系模型 -> 输出

L1. [简单]3.1.1/2 + 3.2.1 + 3.3.1/2 + 3.4.1  <-- 在做：
	1. 构筑了简单的Model+Element+Relation。基本实现，还需要考虑是否改成Element内部全部都是property的方式，这样无论是Elment还是Relation，或者其他的扩展方式都适合。
	2. 需要加入输入和输出。现在脚本的语法还没有确定，要按照上面的具体应用来设计。 [先按照最简单的行分析来进行]
	3. 在main函数中设定输出和输出。作为脚本可以输入，但是没有实现交互模式，以及输出。
		我想做到Model中无论哪种关系，怎么建立起来的，都可以输出成脚本，这就相当于关系模型的保存功能。
		首先所有的高级模块，比如model/process之类的，现在用代码固定，后面将用注册的方式，这样可以通过任意组合来实现不同的功能，现在还没有必要。【 还没有实现 ！！！】
L2. [复杂]3.1.3/4 + 3.2.2 + 3.3.3/4/5 + 3.4.2/2
L3. [实用]3.1.5 + 3.2.3 + 3.3.6 + 3.4.4
L3. [专家]3.2.4

## 问题
	1. 无法要求元素在所有的区域不重名，但是在某个特定区域内可以要求不重名。
	2. 双引号问题：所有的文字可以加入双引号，这样内部的空格也可以包含，但是放入模型时，需要将左右的双引号去掉。
	3. 定义一个元素时，建立显示的映射方法，output可以指定显示的类型和各个显示的部分对应什么。
	4. 执行的语法没有说明，在大量的加入属性后，无法让用户简单的了解怎么使用。
	5. 命令行语句，还不支持换行“\”。
	6. 允许截取大模型中的一部分关系，这个是查询的功能，然后形成新的模型，然后映射到"显示"中。
	8. 还有互动模式，这个可以作为试验某些命令的地方。
	9. output只简单实现了list模式，其他的call和layout还没有区分。
	10. 目前的命令没有修改之前模型的内容的语句。

### 对语法的想法
目前纠结在语法的规定上，不要再在单行的命令语法上徘徊了，需要深入到高级语法上去。
	1. 用 TAG 描述是否很快，很直接？ a.b = c，b是关系名字，a的b是c，也意味着 a和c之间的关系是b。
		比如 我的名字是张三，那么我和张三的关系是名字。
	2. 用 自然语言来说，“主谓宾”是最核心的语句，那么每个部分都可以加入定语或者副词，也就意味着标签/属性。
		另外“介词”怎么考虑？
	
另外一种是按照prolog方式，用括号来表示，比如 R(a, b)，以及设定“规则”，这个其实都满足目前think的需要。
	但是prolog语言本身是服务于逻辑推理的，并不是用来编程，无法满足目前编程的需求，因为目前编程都是基于“动作”的，
	没有固定的规则，只有客户的想法，只有当出现现实的冲突时，功能设计才会分析冲突的原因，指定统一的规则，否则是不管的。
	所以现在的语言重点是实现，而不是推理！
	【这个也是我目前制作think时的最大困惑地方，如何在普通编程中用到关系推理？】

语法中是否可以提供一个造型能力？就是通过简单的记法，转变为正规的关系描述，这样可以缩减描述的大小，以及提供高级扩展功能。

建立更加高级的表达式机制：

Query value=表达式
表达式类似于 c 语言的表达式。


## 代码结构

1. core 是核心，数据结构和增删改查在这里。
2. fwk 是在core基础上的框架，主要是各个应用的模块，作为最基础的扩展。
3. ext 是在core/fwk的基础上扩展的各个模块，是基于实用的扩展。
4. app 是在其他之上建立的主程序和测试程序。还有具体应用环境的扩展。