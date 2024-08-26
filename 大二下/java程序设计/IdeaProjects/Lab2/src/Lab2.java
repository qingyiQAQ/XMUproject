import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Scanner;

public class Lab2 {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        System.out.println("请输入玩家数：");
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();//输入玩家数
        int player[][],level[],num[][];
        int price[]={1,2,4,8,16,32};//记录各个奖项剩余数目
        int zhuangyuan=-1;//状元（其数值即为获得状元的玩家序号）
        player=new int[n][6];//输入玩家数并根据玩家数创建二维数组
        level=new int[n];//用于记录玩家的奖项等级
        for(int i=0;i<n;i++)level[i]=-1;
        num=new int[n][6];//用于记录各个点数的数目
        SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");//生成SHA1PRNG算法加密随机数
        System.out.println("请输入骰子执行方式（1.手动输入点数，2.随机生成点数）：");
        int op = input.nextInt();
        if(op==1)
        {
            for(int i=0;i<n;i++)
            {
                System.out.println("请输入玩家"+(i+1)+"的骰子点数：");
                for(int j=0;j<6;j++)
                {
                    player[i][j]=input.nextInt();
                }
            }//（用于测试）手动输入骰子点数
        }
        if(op==2)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<6;j++)
                {
                    player[i][j]=secureRandom.nextInt(6)+1;
                }
            }//自动生成随机数
        }
        for(int i=0;i<n;i++)
        {
            System.out.print("玩家"+(i+1)+"=");
            for(int j=0;j<6;j++)
            {
                System.out.printf("%d ", player[i][j]);
            }
            System.out.print("\n");
        }//输出各个玩家点数情况
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<6;j++)
            {
                for(int k=0;k<6;k++)
                {
                    if(player[i][j]==k+1)num[i][k]++;
                }
            }//计算各个点数数目
            if(num[i][3]==4&num[i][0]==2)
            {
                level[i]=1;
                if(zhuangyuan==-1||level[i]<level[zhuangyuan]||(level[i]==level[zhuangyuan]&&player[i][0]+player[i][1]+player[i][2]+player[i][3]+player[i][4]+player[i][5]>player[zhuangyuan][0]+player[zhuangyuan][1]+player[zhuangyuan][2]+player[zhuangyuan][3]+player[zhuangyuan][4]+player[zhuangyuan][5]))
                    zhuangyuan=i;
            }
            if(num[i][3]==6)
            {
                level[i]=2;
                if(zhuangyuan==-1||level[i]<level[zhuangyuan]||(level[i]==level[zhuangyuan]&&player[i][0]+player[i][1]+player[i][2]+player[i][3]+player[i][4]+player[i][5]>player[zhuangyuan][0]+player[zhuangyuan][1]+player[zhuangyuan][2]+player[zhuangyuan][3]+player[zhuangyuan][4]+player[zhuangyuan][5]))
                    zhuangyuan=i;
            }
            for(int j=0;j<6&&j!=3;j++)
            {
                if(num[i][j]==6)
                {
                    level[i]=3;
                    if(zhuangyuan==-1||level[i]<level[zhuangyuan]||(level[i]==level[zhuangyuan]&&player[i][0]+player[i][1]+player[i][2]+player[i][3]+player[i][4]+player[i][5]>player[zhuangyuan][0]+player[zhuangyuan][1]+player[zhuangyuan][2]+player[zhuangyuan][3]+player[zhuangyuan][4]+player[zhuangyuan][5]))
                    zhuangyuan=i;
                }
            }
            if(num[i][3]==5)
            {
                level[i]=4;
                if(zhuangyuan==-1||level[i]<level[zhuangyuan]||(level[i]==level[zhuangyuan]&&player[i][0]+player[i][1]+player[i][2]+player[i][3]+player[i][4]+player[i][5]>player[zhuangyuan][0]+player[zhuangyuan][1]+player[zhuangyuan][2]+player[zhuangyuan][3]+player[zhuangyuan][4]+player[zhuangyuan][5]))
                zhuangyuan=i;
            }
            for(int j=0;j<6&&j!=3;j++)
            {
                if(num[i][j]==5)
                {
                    level[i]=5;
                    if(zhuangyuan==-1||level[i]<level[zhuangyuan]||(level[i]==level[zhuangyuan]&&player[i][0]+player[i][1]+player[i][2]+player[i][3]+player[i][4]+player[i][5]>player[zhuangyuan][0]+player[zhuangyuan][1]+player[zhuangyuan][2]+player[zhuangyuan][3]+player[zhuangyuan][4]+player[zhuangyuan][5]))
                    zhuangyuan=i;
                }
            }
            if(num[i][3]==4&num[i][0]!=2)
            {
                level[i]=6;
                if(zhuangyuan==-1||level[i]<level[zhuangyuan]||(level[i]==level[zhuangyuan]&&player[i][0]+player[i][1]+player[i][2]+player[i][3]+player[i][4]+player[i][5]>player[zhuangyuan][0]+player[zhuangyuan][1]+player[zhuangyuan][2]+player[zhuangyuan][3]+player[zhuangyuan][4]+player[zhuangyuan][5]))
                zhuangyuan=i;
            }
            //判断是否是状元
            if(price[1]!=0&&num[i][0]==1&num[i][1]==1&num[i][2]==1&num[i][3]==1&num[i][4]==1&num[i][5]==1){level[i]=7;price[1]--;}
            if(price[2]!=0&&num[i][3]==3){level[i]=8;price[2]--;}
            for(int j=0;j<6&&j!=3;j++)
            {
                if(price[3]!=0&&num[i][j]==4){level[i]=9;price[3]--;}
            }
            if(price[4]!=0&&num[i][3]==2&&num[i][0]!=4&&num[i][1]!=4&&num[i][2]!=4&&num[i][4]!=4&&num[i][5]!=4){level[i]=10;price[4]--;}
            if(price[5]!=0&&num[i][3]==1&&num[i][0]<4&&num[i][1]<4&&num[i][2]<4&&num[i][4]<4&&num[i][5]<4&&!(num[i][0]==1&num[i][1]==1&num[i][2]==1&num[i][3]==1&num[i][4]==1&num[i][5]==1)){level[i]=11;price[5]--;}
        }//判断各个玩家所获得的奖项
        for(int i=0;i<n;i++)
        {
            System.out.print("玩家"+(i+1)+"的奖项为：");
            if(zhuangyuan==i)
            {
                price[0]--;
                switch(level[i])
                {
                    case 1:System.out.print("状元插金花");break;
                    case 2:System.out.print("六博红");break;
                    case 3:System.out.print("六博黑");break;
                    case 4:System.out.print("五王");break;
                    case 5:{if(num[i][3]==1)System.out.print("五子登科带一秀");else System.out.print("五子登科");}break;
                    case 6:System.out.print("状元");break;
                }
            }
            switch(level[i])
            {
                case 7:System.out.print("对堂");break;
                case 8:System.out.print("三红");break;
                case 9:{if(num[i][3]==1)System.out.print("四进带一秀");if(num[i][3]==2)System.out.print("四进带二举");if(num[i][3]==0)System.out.print("四进");}break;
                case 10:System.out.print("二举");break;
                case 11:System.out.print("一秀");break;
            }
            if(level[i]<=6&&i!=zhuangyuan)System.out.print("无");
            System.out.print("\n");
        }//输出各个玩家所获得的奖项
        System.out.print("奖项剩余情况：\n");
        System.out.print("状元："+price[0]+"\n");
        System.out.print("对堂："+price[1]+"\n");
        System.out.print("三红："+price[2]+"\n");
        System.out.print("四进："+price[3]+"\n");
        System.out.print("二举："+price[4]+"\n");
        System.out.print("一秀："+price[5]+"\n");
        //输出奖项剩余情况
    }
}