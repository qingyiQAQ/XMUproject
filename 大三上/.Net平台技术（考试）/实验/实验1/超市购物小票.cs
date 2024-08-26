using System;
using System.Text;

namespace Program3
{

    internal class Program
    {
        static void Main(string[] args)
        {
            List<Item> items = new List<Item>
            {
                new Item("原味鸡", 14, 1),
                new Item("葡式蛋挞", 8.5, 1),
                new Item("中可", 10, 1),
                new Item("燃情孜滋烤鸡腿堡", 23, 1)
            };
            string note = "美团外卖|环保单顾客不需要餐具无需附带餐具";
            Restaurant restaurant = new Restaurant("厦门大学翔安校区", "05922062238", 
                "翔安区香山街道翔安南路4221-126-205号");
            Costomer costomer = new Costomer("陈**先生)--------", "187****1886",
                "厦门大学（翔安校区）（翔安校区国光13）9999--------9999----****");
            DateTime produce_time = new DateTime(1, 1, 1, 11, 48, 0);
            DateTime delivery_time = new DateTime(1, 1, 1, 12, 17, 0);


            PrintReceipt(note, restaurant, items, costomer, 22.6, produce_time, delivery_time);
        }
        static void PrintReceipt(string note, Restaurant restaurant, List<Item> items,
            Costomer costomer ,double preference, DateTime produce_time, DateTime delivery_time)
        {
            string cha1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            string cha2 = "0123456789";
            Random random = new Random();
            StringBuilder stringBuilder = new StringBuilder();
            while (stringBuilder.Length < 2)
            {
                int randomIndex = random.Next(0, cha1.Length);
                char randomChar = cha1[randomIndex];
                stringBuilder.Append(randomChar);
            }
            while (stringBuilder.Length < 5)
            {
                int randomIndex = random.Next(0, cha2.Length);
                char randomChar = cha2[randomIndex];
                stringBuilder.Append(randomChar);
            }
            //随机生成两个大写字母加三个数字作为小票号码
            Console.WriteLine($"{stringBuilder.ToString(),25}");
            Console.WriteLine("-------------------------------------------");
            Console.WriteLine($"备注：{note}");
            Console.WriteLine("-------------------------------------------");
            Console.WriteLine($"餐厅名：{restaurant.Name}");
            Console.WriteLine($"餐厅电话：{restaurant.Phone}");
            Console.WriteLine($"餐厅地址：{restaurant.Address}");
            Console.WriteLine($"姓名：{costomer.Name}");
            Console.WriteLine($"地址：{costomer.Address}");
            Console.WriteLine(costomer.Phone);
            Console.WriteLine("-------------------------------------------");
            Console.WriteLine("-------------------------------------------");
            double total_price = 0,actual_payment;
            foreach (Item item in items)
            {
                item.Print();
                total_price += item.Price * item.Num;
            }
            Console.WriteLine($"总计：{total_price}");
            Console.WriteLine($"优惠：{preference}");
            actual_payment = total_price - preference;
            Console.WriteLine($"实付：{actual_payment}");
            Console.WriteLine($"承诺送达时间：{delivery_time:H:m}");
            Console.WriteLine($"制作时间：{produce_time:H:m}");
            Console.WriteLine("-------------------------------------------");
            DateTime lastDayOfMonth = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.DaysInMonth(DateTime.Now.Year, DateTime.Now.Month));
            Console.WriteLine($"{DateTime.Now:M月1日}-{lastDayOfMonth:M月d日}");//显示当前月份的第一天到最后一天
            Console.WriteLine("                 宅神卡");
            Console.WriteLine("-------------------------------------------");
            Console.WriteLine("            满额外送费最低0元");
            Console.WriteLine("            （详情请见购卡须知）");
            Console.WriteLine("              专享美味超值");
            Console.WriteLine("-------------------------------------------");
            Console.WriteLine("               #限时抢购#");
            Console.WriteLine("*购买前请仔细查看《肯德基付费会员协议》以及宅神卡《购买须知》了解您的相关权利和义务");
            Console.WriteLine("-------------------------------------------");
            Console.WriteLine("外送食品请尽快食用，请妥善保存事物");
            Console.WriteLine("事物不宜裸露在空气中，以免招引虫蝇等");
            Console.WriteLine("           珍惜粮食，按需点餐");
        }
        class Restaurant
        {
            public string Name { get; set; }
            public string Phone { get; set; }
            public string Address { get; set; }
            public Restaurant(string name, string phone, string address)
            {
                Name = name;
                Phone = phone;
                Address = address;
            }
        }
        class Item
        {
            public string Name { get; set; }
            public double Price { get; set; }
            public int Num { get; set; }

            public Item(string name, double price ,int num)
            {
                Name = name;
                Price = price;
                Num = num;
            }

            public void Print()
            {
                Console.WriteLine($"  {Num}  {Name}");
            }
        }
        class Costomer
        {
            public string Name { get; set; }
            public string Phone { get; set; }
            public string Address { get; set; }
            public Costomer(string name, string phone, string address)
            {
                Name = name;
                Phone = phone;
                Address = address;
            }
        }
    }
}
