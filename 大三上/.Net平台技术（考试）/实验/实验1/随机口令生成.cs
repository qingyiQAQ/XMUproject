using System;
using System.Text;
using System.Windows.Forms;

namespace Program1
{
    internal class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            string cha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&()*.,";
            Random random = new Random();
            int length = random.Next(8, 16);
            Console.WriteLine("输入屏蔽字符：");
            char[] charsToRemove = Console.ReadLine().ToCharArray();
            cha = RemoveChar(charsToRemove, cha);
            string s = GenerateRandomPassword(length, cha);
            Console.WriteLine($"已生成口令：{s}");
            Clipboard.SetText(s);
            Console.WriteLine("已自动复制到剪切板");
        }
        static string RemoveChar(char[] charsToRemove, string cha)
        {
            string result = cha;
            foreach (char c in charsToRemove)
            {
                result = result.Replace(c.ToString(), string.Empty);
            }
            return result;
        }
        //从字符串cha中剔除charsToRemove中的字符，返回剔除字符后的字符串
        static string GenerateRandomPassword(int length, string validChars)
        {
            Random random = new Random();
            StringBuilder passwordBuilder = new StringBuilder();

            while (passwordBuilder.Length < length)
            {
                int randomIndex = random.Next(0, validChars.Length);
                char randomChar = validChars[randomIndex];
                passwordBuilder.Append(randomChar);
            }

            return passwordBuilder.ToString();
        }
        //随机生成包含字符串validChars中字符且长度为length的字符串并返回
    }
}
