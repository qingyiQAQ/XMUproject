#RISC-Vð�ݷ����������        sort3_riscv.asm               ��5�����ݽ������򣨴Ӵ�С���������У�        
# 5�������ɳ������ô���ڵ�ַΪ0��4��8��12��16�����ݴ洢����             
#  ���кõ�������Ȼ���ڵ�ַΪ0��4��8��12��16�����ݴ洢����     

main:
	ori  	a2,zero,5  			#a2=5

	ori 	a1, zero, 3 			# a1 = 3
	sw 	a1, 0(zero)                             		# 3 -> (0)
	ori 	a1, zero, 1 			# a1 = 1
	sw 	a1, 4(zero)                             		# 1 -> (4)
	ori 	a1, zero, 5 			# a1 = 5
	sw 	a1, 8(zero)                             		# 5 -> (8)
	ori 	a1, zero, 2			# a1 = 2
	sw 	a1, 12(zero)                             	# 2 -> (12)
	ori 	a1, zero, 4			# a1 = 4
	sw 	a1, 16(zero)                             	# 4 -> (16)

	ori  	a4,zero,1  			
	ori  	a5,zero,4  			
	ori  	a6,zero,-1  			
loop1:
	beq  	a2,a4,finish  			
	ori  	a3,zero,1  			
	ori  	a7,zero,0                                 		
	ori  	s8,zero,4				
loop2:
	sltu  	s11,a3,a2 			
	beq  	s11,zero,loop3
	lw 	s9,0(a7)     			
	lw 	s10,0(s8)    			
	sltu 	s11,s10,s9 			#�������У��Ӵ�С
	beq 	s11,a4,loop4                            
	sw 	s10,0(a7)  			
	sw 	s9,0(s8)   				
	jal 	zero,loop4
loop3:
   	add 	a2,a2,a6
   	jal 	zero,loop1
loop4:
   	add 	a3,a3,a4 				
   	add 	a7,a7,a5
   	add 	s8,s8,a5
   	jal 	zero,loop2
finish:
	jal 	zero,finish

