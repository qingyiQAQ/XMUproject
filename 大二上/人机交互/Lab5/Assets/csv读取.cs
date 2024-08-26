using System;
using System.Data;
using System.IO;
using System.Text;
using UnityEngine;
using UnityEngine.UI;

public class csv读取 : MonoBehaviour
{
    public Text zhanghao;
    public Text mima;
    public Text time;
    public Text borntime;
    void Start()
    {
        string filePath = Application.streamingAssetsPath + "\\账号密码储存.csv";
        DataTable dt = OpenCSV(filePath);
        zhanghao.text="账号="+dt.Rows[0][0];
        mima.text="密码="+dt.Rows[0][1];
        time.text="登录时间="+dt.Rows[0][2];
        borntime.text="我的出生日期"+dt.Rows[1][2];
    }

    public static DataTable OpenCSV(string filePath)//从csv读取数据返回table
    {
        DataTable dt = new DataTable();
        using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read))
        {
            using (StreamReader sr = new StreamReader(fs, Encoding.UTF8))
            {
                //记录每次读取的一行记录
                string strLine = "";
                //记录每行记录中的各字段内容
                string[] aryLine = null;
                string[] tableHead = null;
                //标示列数
                int columnCount = 0;
                //标示是否是读取的第一行
                bool IsFirst = true;
                //逐行读取CSV中的数据
                while ((strLine = sr.ReadLine()) != null)
                {
                    if (IsFirst == true)
                    {
                        tableHead = strLine.Split(',');
                        IsFirst = false;
                        columnCount = tableHead.Length;
                        //创建列
                        for (int i = 0; i < columnCount; i++)
                        {
                            DataColumn dc = new DataColumn(tableHead[i]);
                            dt.Columns.Add(dc);
                        }
                    }
                    else
                    {
                        aryLine = strLine.Split(',');
                        DataRow dr = dt.NewRow();
                        for (int j = 0; j < columnCount; j++)
                        {
                            dr[j] = aryLine[j];
                        }
                        dt.Rows.Add(dr);
                    }
                }
                if (aryLine != null && aryLine.Length > 0)
                {
                    dt.DefaultView.Sort = tableHead[0] + " " + "asc";
                }
                sr.Close();
                fs.Close();
                return dt;
            }
        }
    }
}
