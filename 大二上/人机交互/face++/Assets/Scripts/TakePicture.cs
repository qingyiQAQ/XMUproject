using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using UnityEngine.SceneManagement;

public class TakePicture : MonoBehaviour
{
    int cameraId = 0;
    WebCamTexture currentWebCam;
    public RawImage cameraContent;

    void Start()
    {
        StartCoroutine(Call());
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space)) // 按空格取一张照片
        {
            StartCoroutine(SaveToPng(cameraContent.texture));
            currentWebCam.Stop();
            SceneManager.LoadScene(1);
        }
        if (Input.GetKeyDown(KeyCode.C))
            SwitchCamera();
    }

    public IEnumerator Call()
    {
        // 请求权限
        yield return Application.RequestUserAuthorization(UserAuthorization.WebCam);

        if (Application.HasUserAuthorization(UserAuthorization.WebCam) && WebCamTexture.devices.Length > 0)
        {
            // 创建相机贴图
            currentWebCam = new WebCamTexture(WebCamTexture.devices[cameraId].name, 1280, 720, 30);
            cameraContent.texture = currentWebCam;
            currentWebCam.Play();
        }
        else Debug.LogError("未获取摄像头权限");
    }

    //切换摄像头
    public void SwitchCamera()
    {
        if (WebCamTexture.devices.Length < 1)
            return;

        if (currentWebCam != null)
            currentWebCam.Stop();

        cameraId++;
        cameraId = cameraId % WebCamTexture.devices.Length;

        // 创建相机贴图
        currentWebCam = new WebCamTexture(WebCamTexture.devices[cameraId].name, 1280, 720, 30);
        cameraContent.texture = currentWebCam;
        currentWebCam.Play();
    }

    //保存png至StreamingAssets
    IEnumerator SaveToPng(Texture t)
    {
        yield return new WaitForEndOfFrame();
        Texture2D png = new Texture2D(1280, 720, TextureFormat.ARGB32, false);
        png.ReadPixels(new Rect(0, 0, 1280, 720), 0, 0);
        png.Apply();
        byte[] bytes = png.EncodeToPNG();
        FileStream picFile = File.Open(Application.streamingAssetsPath + "/1.png", FileMode.Create);
        BinaryWriter writer = new BinaryWriter(picFile);
        writer.Write(bytes);
        writer.Flush();
        writer.Close();
        picFile.Close();
        Destroy(png);
        png = null;
        Debug.Log("图片保存成功，文件名：1.png");
    }
}
