#�����߽ṹMIPS���������Գ���                             test1.asm
#����5��ָ�� ��lw��sw��beq��addi��slt��                 
#����ִ����   100��101��102��Ԫ�����ݷֱ�Ϊ��8��9��1

main:
 	addi $s0,$zero,8                          #s0=8
 	sw $s0,1024($zero)		    #s0=8 ���浽(1024����100��Ԫ)

 	addi $s0,$zero,9                        #s0=9
 	sw $s0,1028($zero)		   #s0=9 ���浽(1028����101��Ԫ)

 	lw $s1,1024($zero)                    #$s1=8
	lw $s2,1028($zero)                	   #$s2=9

                slt $s3,$s1,$s2                            # s1 < s2       s3=1

 	beq $s1,$s2,loop1   	  #s1������s2      ִ����һ��ָ��

                sw $s3,1032($zero)                   #s3=1 ���浽(1032����102��Ԫ)        

                beq $zero,$zero,loop2	  #תloop2                       

loop1:
               addi $s4,$zero,2                        #s4=2                                 		����ָ���ִ�е�
               sw $s4,1032($zero)                   #s4=2 ���浽(1032����102��Ԫ)            ����ָ���ִ�е�   

loop2:
              beq $zero,$zero,loop2	  #תloop2             ��ѭ��