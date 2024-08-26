using System.Collections;
using System.Collections.Generic;
using System.IO;
using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Networking;
using Newtonsoft.Json.Linq;
using Spore.Unity.UI;

public class ShowInfo : MonoBehaviour
{
    public RawImage facePicture;
    public Text faceInfo;

    public Color32[] colorSet = new Color32[5];
    List<GameObject> UILines = new List<GameObject>();
    public GameObject UILinePrefab;
    public Transform LinesParent;

    // Start is called before the first frame update
    IEnumerator Start()
    {
        //在屏幕上显示图片
        FileStream fs = new FileStream(Application.streamingAssetsPath + "/1.png", FileMode.Open);
        byte[] imgByte = new byte[fs.Length];
        fs.Read(imgByte, 0, imgByte.Length);
        fs.Close();
        Texture2D tex = new Texture2D(100, 100);
        tex.LoadImage(imgByte);
        facePicture.texture = tex;

        //Face++ Http请求
        List<IMultipartFormSection> formData = new List<IMultipartFormSection>();
        formData.Add(new MultipartFormDataSection("api_key", "gP3mrZW05Yjd8IKqPcSo5NAK5KGv-r7X"));
        formData.Add(new MultipartFormDataSection("api_secret", "EUh7MZxYKpyE-BN9pn-ST-RFUBwe7qIe"));
        formData.Add(new MultipartFormDataSection("return_landmark", "1"));
        string imgStr = Convert.ToBase64String(imgByte);
        formData.Add(new MultipartFormDataSection("image_base64", imgStr));
        formData.Add(new MultipartFormDataSection("return_attributes", "gender,age,emotion,beauty"));
        UnityWebRequest www = UnityWebRequest.Post("https://api-cn.faceplusplus.com/facepp/v3/detect", formData);
        yield return www.SendWebRequest();

        while (true)
        {
            if (www.result == UnityWebRequest.Result.ConnectionError || www.result == UnityWebRequest.Result.DataProcessingError || www.result == UnityWebRequest.Result.ProtocolError)
            {
                Debug.Log(www.error);
                break;
            }
            else if (www.result == UnityWebRequest.Result.Success)
            {
                JObject jsonObject = JObject.Parse(www.downloadHandler.text);
                int face_num = (int)jsonObject["face_num"];
                faceInfo.text = "";
                print("face_num: " + face_num);
                for (int i = 0; i < face_num; i++)
                {
                    //绘制人脸矩形
                    int x = (int)jsonObject["faces"][i]["face_rectangle"]["left"];
                    int y = Screen.height - (int)jsonObject["faces"][i]["face_rectangle"]["top"];
                    Rect face_rectangle = new Rect(x, y, (int)jsonObject["faces"][i]["face_rectangle"]["width"], (int)jsonObject["faces"][i]["face_rectangle"]["height"]);
                    DrawRectangle(face_rectangle, colorSet[i % 5]);

                    //输出性别 年龄 情绪
                    string gender = jsonObject["faces"][i]["attributes"]["gender"]["value"].ToString();
                    int age = (int)jsonObject["faces"][i]["attributes"]["age"]["value"];
                    float emo_anger = (float)jsonObject["faces"][i]["attributes"]["emotion"]["anger"];
                    float emo_disgust = (float)jsonObject["faces"][i]["attributes"]["emotion"]["disgust"];
                    float emo_fear = (float)jsonObject["faces"][i]["attributes"]["emotion"]["fear"];
                    float emo_happiness = (float)jsonObject["faces"][i]["attributes"]["emotion"]["happiness"];
                    float emo_neutral = (float)jsonObject["faces"][i]["attributes"]["emotion"]["neutral"];
                    float emo_sadness = (float)jsonObject["faces"][i]["attributes"]["emotion"]["sadness"];
                    float emo_surprise = (float)jsonObject["faces"][i]["attributes"]["emotion"]["surprise"];
                    faceInfo.text += "face_id: " + (i + 1) + "\n";
                    faceInfo.text += "gender: " + gender + "\n";
                    faceInfo.text += "age: " + age + "\n";
                    faceInfo.text += "emotion_anger: " + emo_anger + ", ";
                    faceInfo.text += "emotion_disgust: " + emo_disgust + ", ";
                    faceInfo.text += "emotion_fear: " + emo_fear + ", ";
                    faceInfo.text += "emotion_happiness: " + emo_happiness + "\n";
                    faceInfo.text += "emotion_neutral: " + emo_neutral + ", ";
                    faceInfo.text += "emotion_sadness: " + emo_sadness + ", ";
                    faceInfo.text += "emotion_surprise: " + emo_surprise + "\n";
                }
                break;
            }
            else if (www.result == UnityWebRequest.Result.InProgress)
            {
                print("in progress");
                yield return null;
            }
        }

    }

    //绘制矩形
    public void DrawRectangle(Rect rect, Color32 tempColor)
    {
        GameObject temp = Instantiate(UILinePrefab);
        float X;
        float Y;
        X = rect.x;
        Y = rect.y;
        temp.GetComponent<LineUIMesh>().StartPosition = new Vector2(X, Y);
        X = rect.x;
        Y = rect.y - rect.height;
        temp.GetComponent<LineUIMesh>().EndPosition = new Vector2(X, Y);
        temp.GetComponent<LineUIMesh>().color = tempColor;
        temp.transform.SetParent(LinesParent);
        UILines.Add(temp);

        X = rect.x;
        Y = rect.y - rect.height;
        temp = Instantiate(UILinePrefab);
        temp.GetComponent<LineUIMesh>().StartPosition = new Vector2(X, Y);
        X = rect.x + rect.width;
        Y = rect.y - rect.height;
        temp.GetComponent<LineUIMesh>().EndPosition = new Vector2(X, Y);
        temp.GetComponent<LineUIMesh>().color = tempColor;
        temp.transform.SetParent(LinesParent);
        UILines.Add(temp);

        X = rect.x + rect.width;
        Y = rect.y - rect.height;
        temp = Instantiate(UILinePrefab);
        temp.GetComponent<LineUIMesh>().StartPosition = new Vector2(X, Y);
        X = rect.x + rect.width;
        Y = rect.y;
        temp.GetComponent<LineUIMesh>().EndPosition = new Vector2(X, Y);
        temp.GetComponent<LineUIMesh>().color = tempColor;
        temp.transform.SetParent(LinesParent);
        UILines.Add(temp);


        X = rect.x + rect.width;
        Y = rect.y;
        temp = Instantiate(UILinePrefab);
        temp.GetComponent<LineUIMesh>().StartPosition = new Vector2(X, Y);
        X = rect.x;
        Y = rect.y;
        temp.GetComponent<LineUIMesh>().EndPosition = new Vector2(X, Y);
        temp.GetComponent<LineUIMesh>().color = tempColor;
        temp.transform.SetParent(LinesParent);
        UILines.Add(temp);
    }
}