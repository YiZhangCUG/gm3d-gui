# gm3d-gui程序说明书

gm3d是一个开源的直角坐标系下的三维重磁场建模与正演的命令行工具。它能够以方块为基本的建模单元构建复杂的三维密度或磁化率模型并正演计算模型的重磁数据及各方向梯度数据等。

## 程序界面说明

### 建模界面

![建模界面](assert/fig-1.png)

![模型添加界面](assert/fig-2.png)

### 正演界面

![正演界面](assert/fig-3.png)

## 参数与文件说明

### Msh本文文件格式

文本格式Gmsh模型文件（.msh）主要格式如下所示。在格式描述中变量名称以尖括号包围，默认值或数据类型以等号给出。格式注释以！！开头（注意实际文件中无此特性，仅为方便说明之用）。


```
！！网格文件类型 文件类型=0表示为ASCII码文本文件 （必需）
$MeshFormat
<版本号=2.2> <文件类型=0> <浮点字符长度=8>
$EndMeshFormat
！！物理组名称 （非必需）
$PhysicalNames
<名称个数=int>
<物理维度=1|2|3> <物理组标签=int> <物理组名称="string">
...
$EndPhysicalNames
！！点描述（必需）
$Nodes
<点个数=int>
<点编号=int> <x坐标=double> <y坐标=double> <z坐标=double>
...
$EndNodes
！！几何元素描述（必需） 不同几何元素的类型编号请参考Gmsh说明文档 第一个标签为物理组 第二个标签为几何组
！！元素顶点索引的排序请参考Gmsh说明文档
$Elements
<几何元素的个数=int>
<元素编号=int> <元素类型编码=int> <标签个数=int> <标签=int> <标签=int>... <元素顶点索引=int> <元素顶点索引=int>...
...
$EndElements
！！点数据描述 字符串标签一般即为此数据的名称（非必需）
$NodeData
<字符串标签个数=1>
<字符串标签="string">                           ！！数据名称
<浮点标签个数=1>
<浮点标签=double>                              ！！时间戳
<整形标签个数=3>
<整形标签=int>                                 ！！时间排序
<整形标签=1>                                   ！！一维标量
<整形标签=int>                                 ！！数据个数
<点索引=int> <数据值=double>
...
...
$EndNodeData
！！元素数据描述 字符串标签一般即为此数据的名称（非必需）
$ElementData
<字符串标签个数=1>
<字符串标签="string">                           ！！数据名称
<浮点标签个数=1>
<浮点标签=double>                              ！！时间戳
<整形标签个数=3>
<整形标签=int>                                 ！！时间排序
<整形标签=1>                                   ！！一维标量
<整形标签=int>                                 ！！数据个数
<元素索引=int> <数据值=double>
...
...
$EndElementData
！！元素顶点数据描述 字符串标签一般即为此数据的名称（非必需）
$ElementNodeData
<字符串标签个数=1>
<字符串标签="string">                           ！！数据名称
<浮点标签个数=1>
<浮点标签=double>                              ！！时间戳
<整形标签个数=3>
<整形标签=int>                                 ！！时间排序
<整形标签=1>                                   ！！一维标量
<整形标签=int>                                 ！！数据个数
<元素索引=int> <元素的顶点数据个数> <数据值=double> <数据值=double>...
...
...
$EndElementNodeData
```

### 模型参数文件

模型参数文件中各行均为一个完整的模型体的信息描述，包含以下部分：
```
<模型类型> <赋值类型> <物理属性值> <几何属性参数>
```
其中：

* <模型类型>包括`regular_block`，`tilted_block`，`sphere`和`interface`四种类型。
* <赋值类型>包含`add`，`replace`和`erase`三种类型。特别的，对于`interface`类型的模型我们还需要制定操作的对象为界面上`top`或下`bot`，并与前面的赋值类型通过斜杠链接。
* <物理属性值>为模型体的密度或磁化率值。
* <几何属性参数>模型体的几何参数依据模型类型各不相同，详见帮助信息。

### 观测点文件

观测点是一个简单的文本文件，文件每行包含观测点的y（东）、x（北）与z（高程）坐标。

### 界面文件

界面文件为一个简单的文本描述的网格文件，文件头需包含"#range=\<xmin\>/\<dx\>/\<xmax\>/\<ymin\>/\<dx\>/\<ymax\>"信息。文件每行包含高程点的y（东）、x（北）与z（高程）坐标。