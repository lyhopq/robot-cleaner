# 题目设计

扫地机器人(robot cleaner)，又称自动打扫机、智能吸尘器等。能凭借一定的人
工智能，自动在房间内完成地板清理工作。
Bosch公司是领先的扫地机器人制造商。Bosch研发了一款Robot，它接受远端
遥感指令，并完成一些简单的动作。
为了方便控制Robot的导航，工程师使用三元组(x, y, d)来表示Robot的位置信息；
其中(x,y)表示Robot的坐标位置，d表示Robot的方向(包括East, South, West,
North四个方向)。假设Robot初始位置为(0, 0, N)，表示Robot处在原点坐标、并朝
向北。

## 需求一

当Robot收到LEFT指令后，Robot向左转90度；当Robot收到RIGHT指令后，
Robot向右转90度；
例如：Robot原来在(0, 0, N)，执行LEFT指令后，新的位置在(0, 0, W)。

## 需求二

当Robot收到FORWARD指令后，Robot保持方向，并向前移动一个坐标；当Robot
收到BACKWARD指令后，Robot保持方向，并向后移动一个坐标；
例如：原来在(0, 0, E)，执行完FORWARD指令后，新的位置为(1, 0, E)。
注意：必须采用TDD方式进行软件设计和实现。

## 需求三

当Robot收到ROUND指令后，Robot顺时针旋转180度掉头；
例如：原来在(1, 0, E)，执行完ROUND指令后，新的位置为(1, 0, W)。
注意：必须持续地重构实现和测试代码，始终保持代码整洁干净。

## 需求四

当Robot收到FORWARD(n)指令后，Robot保持方向，向前移动n个坐标；当
Robot收到BACKWARD(n)指令后，Robot保持方向，分别向后移动n个坐标；其
中n为正整数[1..10]。
例如：原来在(1, 0, E)，执行FORWARD(2)指令后，新的位置为(3, 0, E)。

## 需求五

当Robot收到一系列组合指令时，能够依次按指令完成相应的动作。
例如：收到指令序列：[LEFT, FORWARD, RIGHT, BACKWARD, ROUND,
FORWARD(2)]，将依次执行：向左转90度；保持方向并向前移动一个坐标；向右转
90度；保持方向并向后退一个坐标；顺时针旋转180度掉头；保持方向向前移动2个坐标。

## 需求六

Robot收到REAPT(instruction, n) 指令后，它会循环执行instruction指令n次。
其中instruction指令指的是：n在[1..10]范围之间。
例如：原来在(1, 0, E)，执行REAPT(FORWARD(2), 2)指令后，新的位置为(5, 0,E)。

## 需求七
当Robot尝试执行指令时，如果超出指定坐标系的范围，则Robot进入保护模式，它会一直尝试执行[LEFT, FORWARD]，直到成功为止；
例如：坐标范围为[6,6]，当原来的位置为(6,6,N)时，执行FORWARD指令，尝试失败，进入保护模式；
尝试第一次[LEFT, FORWARD]指令，依然失败；再尝试一次[LEFT, FORWARD]，尝试成功，新位置为(6,5,S)。
