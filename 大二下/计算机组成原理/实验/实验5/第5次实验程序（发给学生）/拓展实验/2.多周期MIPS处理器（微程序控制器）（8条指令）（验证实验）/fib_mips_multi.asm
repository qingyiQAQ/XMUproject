#MIPS程序    计算费波那契数列                           n=10（可以改变），计算好的n+1个数（0、1、1、2、3、5、8、13、21、34、……）保存在地址为1024、1028、1032、1036、...的数据存储器中

main:
                addi $s2,$zero,10               		# $s2=n=10        

	addi $s1,$zero,0			# $s1=0 		
	sw $s1,1024($zero)                                 # 0 -> (1024)

                addi $s1,$zero,1			# $s1=1 	
	sw $s1,1028($zero)			# 1 -> (1028)

	sw $s1,1032($zero)			# 1 -> (1032)

                addi $s3,$zero,2			# $s3 = 2
                addi $s4,$zero,1			# $s4 = 1
                addi $s5,$zero,1			# $s5 = 1
loop:
                add $s6,$s4,$s5			# $s4+$s5 -> $s6	
                addi $s4,$s5,0			# $s5 -> $s4	
                addi $s5,$s6,0			# $s6 -> $s5	
                addi $s3,$s3,1			# $s3+1 -> $s3	
                add $s7,$s3,$s3			# $s3+$s3 -> $s7
                add $s0,$s7,$s7			# $s7+$s7 -> $s0	
                sw $s6,1024($s0)                		# $s6 -> 1024($s0)	
	beq $s2,$s3,end			# if $s2 = $s3 goto end	
	beq $zero,$zero,loop		# goto loop	
end:
	addi   $v0,$zero,10         		# 10号系统调用
	syscall                  			# 程序退出
