using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;

public class MovingBlock : MonoBehaviour
{
    public PlayableDirector timeline;

    // Start is called before the first frame update
    void Start()
    {
        if (timeline != null)
        {
            timeline.Play();
        }
    }

    // Update is called once per frame
    void Update()
    {
        // 如果Timeline播放完成，则重新开始播放
        if (timeline != null && timeline.state != PlayState.Playing)
        {
            timeline.time = 0; // 重置时间轴
            timeline.Play();   // 重新开始播放
        }
    }
}
