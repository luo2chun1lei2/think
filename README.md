# 思考

【满足要求的最简洁的实现，才是最好的实现。】

## 目的
研究使用工具辅助思考。
我们在思考问题的时候，大部分集中在三个方面：观察、分析和影响。
观察是研究事物的表现，不过随着分析和影响的深入，会修改观察的结果，甚至重新观察目标。
分析是在观察的结果上，用科学的方法去归纳和解释事物的运行的规律，当然这些规律不一定是正确的，也可能只是其中的一种解释。
最后是影响，仅仅是脱离于研究目标之外，是很难搞明白的，而且有些情况下，观察者（我们）也处于和研究目标在一起的情况，
所以在规划好的影响下，进行观察和分析，是能够拿到更加准确的研究信息。

本软件重点在分析，它通过描述目标的关系，形成“事物之间的关联”。因为分析本身必须符合逻辑规则，
所以针对关联可以进行分析，而且可以加速观察者的能力。

目前使用的程序，大部分是“动作”语句，也就建立“函数”(function)为基础的软件系统，
然后这些函数会根据输入改变系统各个部分的状态，无论怎么改变都需要保持系统的各个部分状态的一致性。
它们的流程是，当“触发”(Trigger)出现后，一个一个函数调用起来，改变系统的各个部分。

我考虑的这个系统在现有系统中需要提高一步，参考prolog语言的做法：
	1. 系统的核心是关系（Relation），而不是函数，函数是用于建立、删除、修改“关系”。
	2. 建立后的系统，根据关系可以进行查询、判断和分析。这些是当前语言系统不足的，当前系统只能得到一致的状态，
		但是状态中间的关系是丢失的，没有的，需要用户自己在思想中建立。
	3. 关系不仅仅可以用来建立系统的某个状态内的各个部分之间的关系，实际上也可以建立不同状态之间的关系。
		系统根据建立的关系来进行运转。这个运转是“衍生关系”（extened relation），就是`if条件`的表达式。
		if(a > 2) { sum = a * b; }
		else { sum = a + 1; }
		利用“衍生关系”，就可以在系统的不同状态之间迁移，在某些条件具备时。
	4. 系统在定好的关系中，也可以按照关系进行运行，这就能够将此系统应用在实际的项目中。
		比如 `data -map-> display`，这样如果实现了`map`后，那么当data改变后，就会改变display了。
## 要求
	1. 加入、保存、查询和删改关联关系。
	2. 根据关联关系，得出更多的关联的其他信息，比如衍生关系、组合关系，以及约束关系等。
	3. 可以按照关联关系进行系统的演化，得出系统是否有问题。

## 设计
因为这个是尝试性的软件，所以主体采用循序渐进的开发方法，每一步都要简单、可以测试、有一定的实用行。
下面是从不同的方面来总结软件的功能都有哪些，按照从简单到复杂的方向添加。后面会根据这些功能进行组合成工程进度安排。
第一层关系的应用就是查询之类的，第二层则是根据关系来运行系统，这个就可以应用到真实系统中了。

### 元素设计
【注意：不要搞混乱，一种是关系本身的查询等，第二种是建立、修改、删除关系的动作，这两个要区分开类型】
	1. 元素(Element)是所有对象的基类。
		一个元素可以拥有任意的属性(property)，这些property都有值，值可以是任意的元素。
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
		e0(xingming="luocl", old=43, sex="male")
		```

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
		// 【怎么知道是relation还是普通elment，或者是不需要区分？】
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
	3. 表达式
		多个元素和关系可以形成一个组合元素(combined element)，此组合元素对外的关系就是内部所有元素对外关系。
		当然，多个关系也可以组合成一个关系(combined relation=combined element)。
		可以将关系和元素组成一个有意义的组合，形成一个“组合对象“，这个就是表达式。

		```python
		Value : set_value/get_value -> int/double/string.
		```

		表达式是各种元素的有效组合，可以是(等号右边的)
		```python
			expr = a
			expr = a.b
			expr = (a + 3) / 2
			expr = (a.b + 3) / 2
		```

		还有一种再生关系
		```python
			if (a == b) {
				c = a + 3
			} else {
				c = a + b
			}
		```
		上面的关系是在`a==b`的基础上建立的，所以是再生的关系。

		表达式用另外的更加通用的描述方法
		```python
			expr = /( +(a.b, 3), 2)
			expr = f1( f2(a, b), c) # 更加的通用！但是不符合一般写法。
		```

	4. 推导：从已有条件，得出一个非内在的结果，是推导条件。根据推导条件推导出需要查询的结果。【其实推导也是在建立新的关系，当条件成立的时候】
		可以参考“prolog的推理公式”，就能将逻辑组合出来：符合条件，就能达成什么情况。达成什么情况，就会出现必要条件。（充分和必要条件）

		推导描述的是`a == b`成立时，得出`c =1`。
		```python
		c=1 :- a==b
		```
		
	5. 将形成关系做成一个函数
		```python
		Relation r(a, b, c) {
			rrr(a, b, c)
			bbb(d, e, f)
		}
		```
	6. 种类(kind)是两个方面，一个方面是可以用于“检测匹配”，比如接口，凡是符合这个接口的，就都可以用。
        另外一个作用可以是模板，这样就不用每个对象重复实现自己的逻辑，但是它要求必须是通用的逻辑，而不能是单独元素的实现。
		如果是接口的定义：
		```python
			Interface ABC {
				father; // 必须有的属性
				mather;
				walk(); // 比如有的函数？【函数在这里有用吗？】
			}
		```
		如果是模板：
		```python
			Template ABC {
				
			}
		```
	7. 允许用户自定义种类。
		必须有类型，否则无法创建具有特定功能的元素，只能包含有许多通用的属性！
		目前的语法只有基本的元素和关系，还有表达式，所以类型也只能提供他们这些元素的组合。

		```python
		Relation abc(a, b, c)
		{
			c = a + b
		}
		abc(1, 2, sum) # 设定了 sum 和 1、2 的关系。
		```

		```python
		# 这个是新的元素，设定了一个元素。
		Element abc(old, sex)
			self.old = old
			self.sex = sex
		```
	7. 实际和复杂的表达式
		```python
		mdl() { // ()属性，{} 区域

		task0(desc="总任务")

		task1( desc="任务1")
		task1_1( desc="任务1.1")
		task1_2( desc="任务1.2")
		task1_3( desc="任务1.3")

		task2( desc="任务2")
		task2_1( desc="任务2.1")
		task2_1_1( desc="任务2.2.1")

		task3( desc="任务3")
		# 描述关系
		own( from=task0 to=task1)
		own( from=task0 to=task2)
		own( from=task0 to=task3)

		own( from=task1 to=task1_1)
		own( from=task1 to=task1_2)
		own( from=task1 to=task1_3)

		own( from=task2 to=task2_1)
		own( from=task2_1 to=task2_1_1)
		}
		```
	8. 动作怎么办？
		```python
		graphviz(option=svg, type=list)
		output(mdl, graphviz)  # 建立mdl和graphviz的关系
		```

### 模型设计【这部分是最难的】
	1. 创建模型，容纳元素。
	2. 针对元素的检索、管理等。
	3. 针对整个模型的静态分析。
	4. 针对模型的动态运转。比如关系描述的不再是静态的关系，而是动态的情况，那么系统就需要运转起来看看情况。
	5. 模型之间的转化，比如将模UML型转化为实际的代码，或者画面模型转化为实际的画面。

### 程序设计
	1. 可以进行单元测试。
	2. 可以单独运行。
	3. 接受简单的输入和输出。
	4. 能够有复杂的输入和输出。
	5. 支持不同模型的切换和处理。
	6. 具有图形画面。
	
### 人机接口
	1. API函数。
	2. 脚本可以调用API函数，特点是必须按照循序执行，才能得到正确的模型，所以里面有 if、for等。比如现在张三结交李四。
	   它的本质是通过执行语句，来构造出一个模型。
	   正则表达式的脚本（regrex），和高级的语法脚本（Flex+Bison）。
	3. 关系模型的描述文件。静态类型的结构描述，不是执行的，从任何顺序读取都能够恢复成正确的模型。
	   要求描述语句是静态的，而不是动态的。比如张三是李四的朋友。本质上，它就是模型，至于怎么构造，程序自动完成。
	4. 模型数据的DB数据保存，以后用于数据保存和重现。

## 实现和测试

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
