#MIPS����    ð�ݷ����򣨽������У��Ӵ�С��        sort1_mips.asm               
#�Ƚ�5������3��5��2��1��4����ŵ���ַΪ0��ʼ�����ݴ洢���У�Ȼ�����5������������
#�ó���ִ�к������������ʾ5��4��3��2��1

main:
 	addi $s0,$zero,3                        #��1����=3�������޸ģ����浽(0)
 	sw $s0,0($zero)
 	addi $s0,$zero,5                        #��2����=5�������޸ģ����浽(4)
 	sw $s0,4($zero)
 	addi $s0,$zero,2                        #��3����=2�������޸ģ����浽(8)
 	sw $s0,8($zero)
 	addi $s0,$zero,1                        #��4����=1�������޸ģ����浽(12)
	sw $s0,12($zero)
 	addi $s0,$zero,4                        #��5����=4�������޸ģ����浽(16)
	sw $s0,16($zero)

 	addi $s0,$zero,0          	 #$s0=0                      �������俪ʼ��ַ
 	addi $s1,$zero,16  		 #$s1=16=5*4-4      �������������ַ     
sort_loop:
 	lw $s3,0($s0)                     	#$s3=($s0)
	lw $s4,0($s1)                	#$s4=($s1)
 	slt $t0,$s3,$s4                	#���$s3<$s4������$t0=1��������$t0=0         ��������         �Ӵ�С
 	beq $t0,$zero,sort_next   	#���$t0=0����תsort_nent       
 	sw $s3,0($s1)                	#����($s0)��($s1)
	sw $s4,0($s0)                   	#����($s0)��($s1)
sort_next:
	addi $s1,$s1,-4                        # $s1-4 -> $s1
 	bne $s0,$s1,sort_loop             #���$s0������$s1����תsort_loop
  	addi $s0,$s0,4                         #$s0+4 -> $s0
	addi $s1,$zero,16                   	#$s1=16=5*4-4   �������������ַ              
	bne $s0,$s1,sort_loop 	#���$s0������$s1����תsort_loop

                lw $a0,0($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        0�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,4($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        4�ŵ�Ԫ��
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,8($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        8�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,12($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        12�ŵ�Ԫ��
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,16($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        16�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

	addi   $v0,$zero,10         	# syscall��10��ϵͳ����
	syscall                  		# �����˳�
