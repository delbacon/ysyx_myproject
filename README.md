# "一生一芯"工程项目

这是delbacon的"一生一芯"的工程项目
/npc 包含了一个 riscv32e 的 cpu 核，可以“运行” rtt （ 实际因为没做输入，只能运行（（（ ）
/am-kernels/tests 下包含了一下常用的测试代码，可以通过
```
make ARCH=riscv32e-npc run ALL=xxx 
```
来运行 xxx 测试文档，run改sim,运行成功后会自动启用gtkwave（源文件在 /npc 下），不写 ALL=xxx 则会直接逐个运行所有测试案例
NPCFLAGS=-b 会进入批处理模式，可以批量运行测试案例

[lecture note]: https://ysyx.oscc.cc/docs/
