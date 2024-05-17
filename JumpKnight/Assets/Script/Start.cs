using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class Start : MonoBehaviour
{
     public void jumpToStart(string sceneName)
    {
        SceneManager.LoadScene("LevelOne");
    }

    public void jumpToLevel(string sceneName)
    {
        SceneManager.LoadScene("SelectLevel");
    }

    public void jumpToMenu(string sceneName)
    {
        SceneManager.LoadScene("menu");
    }

    public void jumpToOne(string sceneName)
    {
        SceneManager.LoadScene("LevelOne");
    }

    public void jumpToTwo(string sceneName)
    {
        SceneManager.LoadScene("LevelTwo");
    }

    public void jumpToThree(string sceneName)
    {
        SceneManager.LoadScene("LevelThree");
    }

    public void jumpToFour(string sceneName)
    {
        SceneManager.LoadScene("LevelFour");
    }

}
