#����   lw��sw��beq��slt��addi��add��j  ��7��ָ��ĳ���
#MIPS����    sort1_mips_bus.asm    ���򣨽������У��Ӵ�С�������ۼӺͳ���                       
#�Ƚ�5������4��1��5��2��3����ŵ���ַΪ1024��ʼ�����ݴ洢���У�100�洢��Ԫ����Ȼ�����5������������
#Ȼ����1+2+...+10=55=37H    ������浽1088��ʼ�Ĵ洢��Ԫ�У�110�洢��Ԫ��
main:
 	addi $s0,$zero,4                        #��1����=4�������޸ģ����浽(1024+0)
 	sw $s0,1024($zero)
 	addi $s0,$zero,1                        #��2����=1�������޸ģ����浽(1024+4)
 	sw $s0,1028($zero)
 	addi $s0,$zero,5                        #��3����=5�������޸ģ����浽(1024+8)
 	sw $s0,1032($zero)
 	addi $s0,$zero,2                        #��4����=2�������޸ģ����浽(1024+12)
	sw $s0,1036($zero)
 	addi $s0,$zero,3                        #��5����=3�������޸ģ����浽(1024+16)
	sw $s0,1040($zero)
 	addi $s0,$zero,1024                  #$s0=1024                              �������俪ʼ��ַ
 	addi $s1,$zero,1040  	  #$s1=1040=1024+5*4-4       �������������ַ         5����        
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
	addi $s1,$zero,1040                 #$s1=1040=1024+5*4-4   �������������ַ                5����            
 	beq $s0,$s1,loop2                    #���$s0=$s1����תloop2
 	beq $zero,$zero,sort_loop       #תsort_loop
loop2:
	addi $s0,$zero,10                    # n=10 -> s0                              
	addi $s1,$zero,1               	#        1 -> s1              
	addi $s2,$zero,1               	#        1 -> s2
	addi $s3,$zero,0              	#        0 -> s3           
loop3:
	add $s3,$s3,$s1                 	# s3+s1 -> s3                       
	beq $s1,$s0,loop4              	# ���s1=s0����תloop4       
	add $s1,$s1,$s2                  	# s1+s2 -> s1     
	j loop3
loop4:
	sw $s3,1088($zero)                	# s3 �浽��ַΪ1088�Ĵ洢��Ԫ��
finish:      
	j finish



