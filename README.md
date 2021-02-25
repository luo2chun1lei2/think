思考

【满足要求的最简洁的实现，才是最好的实现。】

1. 目的
研究使用工具辅助思考。
我们在思考问题的时候，大部分集中在三个方面：观察、分析和影响。
观察是研究事物的表现，不过随着分析和影响的深入，会修改观察的结果，甚至重新观察目标。
分析是在观察的结果上，用科学的方法去归纳和解释事物的运行的规律，当然这些规律不一定是正确的，也可能只是其中的一种解释。
最后是影响，仅仅是脱离于研究目标之外，是很难搞明白的，而且有些情况下，观察者（我们）也处于和研究目标在一起的情况，
所以在规划好的影响下，进行观察和分析，是能够拿到更加准确的研究信息。

本软件重点在分析，它通过描述目标的关系，形成“事物之间的关联”。因为分析本身必须符合逻辑规则，
所以针对关联可以进行分析，而且可以加速观察者的能力。

2. 要求
	1. 记录、保存、查询和删改关联关系。
	2. 根据关联关系，得出更多的关联的其他信息，比如衍生关系、组合关系，以及约束关系等。
	3. 可以按照关联关系进行系统的演化，得出系统是否有问题。

3. 设计
【仅仅描写关系并没有什么用，而重要的是针对关系可以做什么。】
因为这个是尝试性的软件，所以主体采用循序渐进的开发方法，每一步都要简单、可以测试、有一定的实用行。
下面是从不同的方面来总结软件的功能都有哪些，按照从简单到复杂的方向添加。后面会根据这些功能进行组合成工程进度安排。

3.1 元素设计
	1. 元素(Element)是所有对象的基类。
	2. 元素延伸出关系(Relation)，关系可以关联多个元素。一个元素可以通过关系关联多个对象。一个元素可以有多个关系。
		a--r-->b : a和b之间有关系r，a的r是b（这种称为关系的属性描述方法）。
	3. 属性(property)或者标签(tag)都相当于一个 a--r-->b 的关联。
		比如说 a的属性r，那么就是说 “a的关系b对应的元素”，这里就是b了。
	4. 多个元素和关系可以形成一个组合元素(combined element)，此组合元素对外的关系就是内部所有元素对外关系。
		当然，多个关系也可以组合成一个关系(combined relation=combined element)。
		可以参考“prolog的推理公式”，就能将逻辑组合出来：符合条件，就能达成什么情况。达成什么情况，就会出现必要条件。（充分和必要条件）
	5. 种类(kind)是元素的类型，类型不仅仅是模板（有统一的制造工厂，以及使用这个类型的函数），而且可以用于“检测匹配”，
		比如某个关系只能针对Person这个种类，那么其他类型元素就无法使用这个关系。
		模板不是种类，比如人有两条腿，而鸡也有两条腿，但是不同的类型。从概念上说，种类等同于功能，而是在此基础上又进行了限制。
	6. 允许用户自定义种类。

3.2 模型设计【这部分是最难的】
	1. 创建模型，容纳元素。
	2. 针对元素的检索、管理等。
	3. 针对整个模型的静态分析。
	4. 针对模型的动态运转。比如关系描述的不再是静态的关系，而是动态的情况，那么系统就需要运转起来看看情况。
	5. 模型之间的转化，比如将模UML型转化为实际的代码，或者画面模型转化为实际的画面。

3.3 程序设计
	1. 可以进行单元测试。
	2. 可以单独运行。
	3. 接受简单的输入和输出。
	4. 能够有复杂的输入和输出。
	5. 支持不同模型的切换和处理。
	6. 具有图形画面。
	
3.4 人机接口
	1. API函数。
	2. 脚本可以调用API函数，特点是必须按照循序执行，才能得到正确的模型，所以里面有 if、for等。比如现在张三结交李四。
	   它的本质是通过执行语句，来构造出一个模型。
	   正则表达式的脚本（regrex），和高级的语法脚本（Flex+Bison）。
	3. 关系模型的描述文件。静态类型的结构描述，不是执行的，从任何顺序读取都能够恢复成正确的模型。
	   要求描述语句是静态的，而不是动态的。比如张三是李四的朋友。本质上，它就是模型，至于怎么构造，程序自动完成。
	4. 模型数据的DB数据保存，以后用于数据保存和重现。

4. 实现和测试

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

5. 语法
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

6. 问题
	1. 无法要求元素在所有的区域不重名，但是在某个特定区域内可以要求不重名。
	2. 双引号问题：所有的文字可以加入双引号，这样内部的空格也可以包含，但是放入模型时，需要将左右的双引号去掉。
	3. 定义一个元素时，建立显示的映射方法，output可以指定显示的类型和各个显示的部分对应什么。
	4. 执行的语法没有说明，在大量的加入属性后，无法让用户简单的了解怎么使用。
	5. 命令行语句，还不支持换行“\”。
	6. 允许截取大模型中的一部分关系，这个是查询的功能，然后形成新的模型，然后映射到"显示"中。
	8. 还有互动模式，这个可以作为试验某些命令的地方。
	9. output只简单实现了list模式，其他的call和layout还没有区分。
