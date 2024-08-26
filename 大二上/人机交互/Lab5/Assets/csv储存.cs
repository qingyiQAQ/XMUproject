using System;
using System.Data;
using System.IO;
using System.Text;
using UnityEngine;
using UnityEngine.UI;

public class csv储存 : MonoBehaviour
{
    void Start()
    {
        //创建表 设置表名
        DataTable dt = new DataTable("Sheet1");
        //创建列 有三列
        dt.Columns.Add("账号");
        dt.Columns.Add("密码");
        dt.Columns.Add("登录时间");
        //创建行 每一行有三列数据
        DataRow dr = dt.NewRow();
        dr["账号"] = PlayerPrefs.GetString("zhanghao");
        dr["密码"] = PlayerPrefs.GetString("mima");
        dr["登录时间"] = (System.DateTime.Now.Year+"/"+System.DateTime.Now.Month+"/"+System.DateTime.Now.Day+"/"+System.DateTime.Now.Hour+":"+System.DateTime.Now.Minute+":"+System.DateTime.Now.Second);
        dt.Rows.Add(dr);
        DataRow dr2 = dt.NewRow();
        dr2["登录时间"] = ("2004/05/19");
        dt.Rows.Add(dr2);
        string filePath = Application.streamingAssetsPath + "\\账号密码储存.csv";
        SaveCSV(filePath, dt);
    }

    // 将DataTable中数据写入到CSV文件中
    public static void SaveCSV(string filePath,DataTable dt)
    {
        FileInfo fi = new FileInfo(filePath);
        if (!fi.Directory.Exists)
        {
            fi.Directory.Create();
        }
        using (FileStream fs = new FileStream(filePath, FileMode.Create, FileAccess.Write))
        {
            using (StreamWriter sw = new StreamWriter(fs, System.Text.Encoding.UTF8))
            {
                string data = "";
                //写入表头
                for (int i = 0; i < dt.Columns.Count; i++)
                {
                    data += dt.Columns[i].ColumnName.ToString();
                    if (i < dt.Columns.Count - 1)
                    {
                        data += ",";
                    }
                }
                sw.WriteLine(data);
                //写入每一行每一列的数据
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    data = "";
                    for (int j = 0; j < dt.Columns.Count; j++)
                    {
                        string str = dt.Rows[i][j].ToString();
                        data += str;
                        if (j < dt.Columns.Count - 1)
                        {
                            data += ",";
                        }
                    }
                    sw.WriteLine(data);
                }
                sw.Close();
                fs.Close();
            }
        }
    }
}
