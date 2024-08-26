using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class 加载 : MonoBehaviour
{
    // Start is called before the first frame update
    public Slider slider;
    void Start()
    {
        slider.value=0;
    }

    // Update is called once per frame
    
    void Update()
    {
        slider.value+=Time.deltaTime*0.5f;
        if(slider.value==1&&SceneManager.LoadSceneAsync(2).progress==1)
        {
            SceneManager.LoadScene(2);
        }
    }
}
