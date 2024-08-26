using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class 登录 : MonoBehaviour
{
    public InputField zhanghao;
    public InputField mima;
    public Text notice;
    // Start is called before the first frame update
    void Start()
    {
        transform.GetComponent<InputField>();
    }
    public void TS()
    {
        if(zhanghao.text!=""&&mima.text!="")
        {
            PlayerPrefs.SetString("zhanghao",zhanghao.text);
            PlayerPrefs.SetString("mima",mima.text);
            SceneManager.LoadScene(1);
        }
        else
        {
            notice.text=("账号或密码输入不完全！");
        }
    }
    // Update is called once per frame
    void Update()
    {
        
    }
}
