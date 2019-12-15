<!--
{
	"author": "lxf",
	"title": "常见汇编指令",
	"date": "2019-05-29 03:06:59",
	"category": "汇编"
}
-->

常见汇编指令
------------------------------------------------------------
#### 指令操作格式：
label:指令助记符 参数1， 参数2， 参数3  

#### 保护模式、实地址模式和虚拟8086模式的指令格式：
![Image 指令格式](img/FormatOfInstructions.png)
-----------------------------------------------

E9 00000000 jmp 地址 直接跳转指令
E9 机器码 = 要跳转的目标地址 - (E9当前指令地址 + 5)(即下一行指令地址)
E8 00000000 call 地址 函数调用
E8 机器码 = 要跳转的目标地址 - (E8当前指令地址 + 5)(即下一行指令地址)
FF 机器码 call 地址变量 间接函数调用

| 指令 | 说明 | Operation | Flags Affected |
|:-----|:----|:---------|:-------------|
|SUB   |减法  |DEST ← (DEST – SRC);|The OF, SF, ZF, AF, PF, and CF flags are set according to the result.|
|CMP   |Compare Two Operands(比较)|temp ← SRC1 − SignExtend(SRC2); ModifyStatusFlags; (* Modify status flags in the same manner as the SUB instruction*)|The CF, OF, SF, ZF, AF, and PF flags are set according to the result.|
|AND   |Logical AND(位逻辑与)|DEST ← DEST AND SRC;|The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result. The state of the AF flag is undefined.|
|TEST  |Logical Compare（逻辑比较，功能跟and一样, 但它不修改运算数, 只修改标志寄存器）|TEMP ← SRC1 AND SRC2;SF ← MSB(TEMP);IF TEMP=0THEN ZF ← 1;ELSE ZF ← 0;FI:PF ← BitwiseXNOR(TEMP[0:7]);CF ← 0;OF ← 0;(* AF is undefined *)|The OF and CF flags are set to 0. The SF, ZF, and PF flags are set according to the result (see the “Operation” section above). The state of the AF flag is undefined.|

MOVS指令：移动数据，内存 - 内存
![Image movs](img/movs.png)

| 指令格式 | 简写 |机器码格式| 说明 |
|:------- | :----|:--------:| :--- |
|MOVS BYTE PTR ES:[EDI], BYTE PTR DS:[ESI] |MOVSB|67A4|将ESI寄存器地址的值复制1个字节到EDI寄存器指向的地址，同时ESI,EDI自增或自减1个字节，方向由EFLAGS或RFLAGS寄存器DF位（方向标志位）决定|
|MOVS WORD PTR ES:[EDI], WORD PTR DS:[ESI] |MOVSW|6667A5|将ESI寄存器地址的值复制2个字节到EDI寄存器指向的地址，同时ESI,EDI自增或自减2个字节，方向由EFLAGS或RFLAGS寄存器DF位（方向标志位）决定|
|MOVS DWORD PTR ES:[EDI], DWORD PTR DS:[ESI] |MOVSD|67A5|将ESI寄存器地址的值复制4个字节到EDI寄存器指向的地址，同时ESI,EDI自增或自减4个字节，方向由EFLAGS或RFLAGS寄存器DF位（方向标志位）决定|
|MOVS QWORD PTR ES:[RDI], QWORD PTR DS:[RSI] |MOVSQ|48A5|将RSI寄存器地址的值复制8个字节到RDI寄存器指向的地址，同时ESI,EDI自增或自减8个字节，方向由EFLAGS或RFLAGS寄存器DF位（方向标志位）决定|

STOS指令：将AL or AX or EAX or RAX的值存储到[EDI] or [RDI]指定的地址单元,EDI or RDI 值自增or自减 [1 2 4 8]
![Image stos](img/stos.png)

REP指令：按计数器（ECX or RCX）中指定的次数重复执行指令
![Image rep](img/rep.png)

JCC指令：条件跳转指令  
![Image rep](img/JCC.png)

------------------------------------------------------------
[返回上级目录](./../../../../categories/assembly/README.md)  |
[返回首页](./../../../../README.md)