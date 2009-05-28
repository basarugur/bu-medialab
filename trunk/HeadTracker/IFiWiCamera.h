///-----------------------------------------------------------------------------
///
/// \file	IFiWiCamera.h
/// \author	Basar Ugur
/// \brief	IEEE1394 / Firewire camera interface, using libdc1394 2.x on Linux
/// \note
///-----------------------------------------------------------------------------

#include "dc1394/dc1394.h"

class IFiWiCamera
{
public:

    dc1394_t *dc_handle;
    dc1394camera_list_t *cam_list;
    dc1394camera_t *camera;
    dc1394video_frame_t *vf;

    dc1394error_t err;

    uint8_t *imageBuf, *imageBufRGB; // direct image buffers

    IFiWiCamera()
    {
        system("../StereoViewer/CameraCleanup");
    }

    ~IFiWiCamera()
    {
        err = dc1394_video_set_transmission(camera, DC1394_OFF);                 /* Stop transmission */

        release_iso_and_bw();

        dc1394_camera_free(camera);                                           /* cleanup and exit */

        dc1394_free(dc_handle);
    }

    bool init()
    {
        // First we try to find a camera
        dc_handle = dc1394_new();
        err = dc1394_camera_enumerate (dc_handle, &cam_list);
        if (err != DC1394_SUCCESS)
        {
            printf("Could not get Camera List: %d\n", err);
            return false;
        }

        if (cam_list->num == 0)
        {
            printf("No cameras found");
            return false;
        }

        // we just use the first one returned
        camera = dc1394_camera_new (dc_handle, cam_list->ids[0].guid);

        if (!camera)
        {
           printf("Failed to initialize camera with guid %d", cam_list->ids[0].guid);
           return false;
        }

        dc1394_camera_free_list(cam_list);

        release_iso_and_bw();

        if ((err = dc1394_video_set_mode(camera, DC1394_VIDEO_MODE_FORMAT7_3)) != DC1394_SUCCESS)
            cout << "Could not set Format7 mode: " << err << endl;

        dc1394_capture_setup(camera, 4, DC1394_CAPTURE_FLAGS_DEFAULT);

        dc1394video_mode_t vm;
        if ((err = dc1394_video_get_mode(camera, &vm)) == DC1394_SUCCESS)
            cout << "Video mode: " << vm << endl;

        dc1394_feature_set_value(camera, DC1394_FEATURE_GAIN, gain);

        uint32_t val;
        dc1394speed_t sp;
        if ((err = dc1394_video_get_iso_channel(camera, &val)) == DC1394_SUCCESS)
            cout << "ISO Channel: " << val << endl;

        if ((err = dc1394_video_get_iso_speed(camera, &sp)) == DC1394_SUCCESS)
            cout << "ISO Speed: " << sp << endl;

        dc1394_video_set_transmission(camera, DC1394_ON);                  /* Start transmission */

        // get a sample video frame for grabbing the resolution:

        if ((err = dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &vf)) != DC1394_SUCCESS ||
            vf == NULL)
        {
            cout << "Could not capture first frame: " << err << endl;
            return false;
        }

        imageBuf = new uint8_t[vf->size[0] * vf->size[1] * 2];
        imageBufRGB = new uint8_t[vf->size[0] * vf->size[1] * 6];

        err = dc1394_capture_enqueue(camera, vf);

        return true;
    }

    void release_iso_and_bw()
    {
        uint32_t val;

        if ( dc1394_video_get_bandwidth_usage(camera, &val) == DC1394_SUCCESS &&
             dc1394_iso_release_bandwidth(camera, val) == DC1394_SUCCESS )
            cout << "Succesfully released " << val << " bytes of Bandwidth." << endl;

        if ( dc1394_video_get_iso_channel(camera, &val) == DC1394_SUCCESS &&
             dc1394_iso_release_channel(camera, val) == DC1394_SUCCESS )
            cout << "Succesfully released ISO channel #" << val << "." <<  endl;
    }

    bool capture_image()
    {
        dc1394video_frame_t* vf_temp;

        dc1394_feature_set_value(camera, DC1394_FEATURE_GAIN, gain);

        bool res = false;

        if ((err = dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &vf_temp)) != DC1394_SUCCESS)
            cout << "Could not capture frame: " << err << endl;
        else if (vf_temp == NULL)
            cout << "Video frame is NULL: " << (vf_temp) << endl;
        else
        {
            vf = vf_temp;
            // cout << "Video frame is OK! e.g. image_bytes: " << vf->image_bytes << endl;

            /* METHOD USING "dc1394video_frame_t"
            dc1394video_frame_t *v_out1, *vout_2;
            v_out1 = new dc1394video_frame_t;
            v_out1->image = new uint8_t[vf->size[0] * vf->size[1] * 6];
            v_out1->color_filter = DC1394_COLOR_FILTER_BGGR;
            v_out1->color_coding = DC1394_COLOR_CODING_RGB8;

            v_out2 = new dc1394video_frame_t;
            v_out2->image = new uint8_t[vf->size[0] * vf->size[1] * 6];
            v_out2->color_filter = DC1394_COLOR_FILTER_BGGR;
            v_out2->color_coding = DC1394_COLOR_CODING_RGB8;

            // MIND YOU: A BUG WALKAROUND! function returns error normally, actually "invalid method" is success
            if ((err = dc1394_deinterlace_stereo_frames(vf, v_out1, DC1394_STEREO_METHOD_INTERLACED)) != DC1394_INVALID_STEREO_METHOD)
                cout << "Could not deinterlace stereo images: " << err << endl;

            cout << v_out1->stride << "--" << v_out1->data_depth << endl;

            if ((err = dc1394_debayer_frames(v_out1, v_out2, DC1394_BAYER_METHOD_SIMPLE)) != DC1394_SUCCESS)
                cout << "Could not apply Bayer conversion: " << err << endl;
            */

            if ((err = dc1394_deinterlace_stereo(vf->image, imageBuf, vf->size[0], vf->size[1]*2)) != DC1394_SUCCESS)
                cout << "Could not deinterlace stereo images: " << err << endl;

            if ((err = dc1394_bayer_decoding_8bit(imageBuf, imageBufRGB,
                                                  vf->size[0], vf->size[1]*2,
                                                  DC1394_COLOR_FILTER_RGGB,
                                                  DC1394_BAYER_METHOD_NEAREST)) != DC1394_SUCCESS)
                cout << "Could not apply Bayer conversion: " << err << endl;

//            FILE *f = fopen("st.ppm", "w+");
//            fprintf(f, "P3\n#st.ppm\n%d %d\n256\n", vf->size[0], vf->size[1]*2);
//            for (int i=0; i<vf->size[1]*2; i++)
//            {   for (int j=0; j<vf->size[0]; j++)
//                    fprintf(f, "%d %d %d ", imageBufRGB[i*vf->size[0]*3 + j*3],
//                                            imageBufRGB[i*vf->size[0]*3 + j*3 + 1],
//                                            imageBufRGB[i*vf->size[0]*3 + j*3 + 2]);
//                fprintf(f, "\n");
//            }
//            fclose(f);

            res = true;
        }

        if ( vf_temp && (err = dc1394_capture_enqueue(camera, vf_temp)) != DC1394_SUCCESS )
            cout << "Could not return frame: " << err << endl;

        return res;
    }
};
