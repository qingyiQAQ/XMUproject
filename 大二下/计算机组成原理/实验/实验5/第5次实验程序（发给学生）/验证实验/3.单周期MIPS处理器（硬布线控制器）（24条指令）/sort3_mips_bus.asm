#MIPS����    sort3_mips_bus.asm    ������򣨽������У��Ӵ�С��     ��ʹ��5��ָ�� ��lw��sw��beq��addi��slt��                 

#�Ƚ�5������3��1��5��2��4����ŵ���ַΪ0��ʼ�����ݴ洢���У�Ȼ�����5������������

.text

main:
 	addi $s0,$zero,3                        #��1����=3�������޸ģ����浽(0)
 	sw $s0,0($zero)
 	addi $s0,$zero,1                        #��2����=1�������޸ģ����浽(4)
 	sw $s0,4($zero)
 	addi $s0,$zero,5                        #��3����=5�������޸ģ����浽(8)
 	sw $s0,8($zero)
 	addi $s0,$zero,2                        #��4����=2�������޸ģ����浽(12)
	sw $s0,12($zero)
 	addi $s0,$zero,4                        #��5����=4�������޸ģ����浽(16)
	sw $s0,16($zero)

 	addi $s0,$zero,0                  	#$s0=0                              �������俪ʼ��ַ
 	addi $s1,$zero,16  	  	#$s1=16=5*4-4       �������������ַ         5����        
sort_loop:
 	lw $s3,0($s0)                     	  #$s3=($s0)
	lw $s4,0($s1)                	  #$s4=($s1)
 	slt $t0,$s3,$s4                	  #���$s3<$s4������$t0=1��������$t0=0        ��������         �Ӵ�С
 	beq $t0,$zero,sort_next   	  #���$t0=0����תsort_nent       
 	sw $s3,0($s1)                	  #����($s0)��($s1)
	sw $s4,0($s0)                   	  #����($s0)��($s1)
sort_next:
	addi $s1,$s1,-4                          #$s1-4 -> $s1
 	beq $s0,$s1,loop1                     #���$s0=$s1����תloop1   
 	beq $zero,$zero,sort_loop        #תsort_loop
loop1:
  	addi $s0,$s0,4                           #$s0+4 -> $s0
	addi $s1,$zero,16                 	#$s1=16=5*4-4   �������������ַ                5����            
 	beq $s0,$s1,loop2                    #���$s0=$s1����תloop2
 	beq $zero,$zero,sort_loop       #תsort_loop
loop2:
 	beq $zero,$zero,loop2	  #תloop2             ��ѭ��