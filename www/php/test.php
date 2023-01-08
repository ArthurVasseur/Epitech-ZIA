<?php
    var_dump($_POST);
    // echo $_POST['submit'];
    // if (isset($_POST['submit'])) {

    //     if (file_exists($_FILES['media-vid']['tmp_name']) && is_uploaded_file($_FILES['media-vid']['tmp_name'])) {

    //         $targetvid     = md5(time());
    //         $target_dirvid = "videos/";

    //         $target_filevid = $targetvid . basename($_FILES["media-vid"]["name"]);

    //         $uploadOk = 0;

    //         $videotype = pathinfo($target_filevid, PATHINFO_EXTENSION);

    // //these are the valid video formats that can be uploaded and
    //               //they will all be converted to .mp4

    //         $video_formats = array(
    //             "mpeg",
    //             "mp4",
    //             "mov",
    //             "wav",
    //             "avi",
    //             "dat",
    //             "flv",
    //             "3gp"
    //         );

    //         foreach ($video_formats as $valid_video_format) {

    //   //You can use in_array and it is better

    //             if (preg_match("/$videotype/i", $valid_video_format)) {
    //                 $target_filevid = $targetvid . basename($_FILES["media-vid"] . ".mp4");
    //                 $uploadOk       = 1;
    //                 break;

    //             } else {
    //           //if it is an image or another file format it is not accepted
    //                 $format_error = "Invalid Video Format!";
    //             }

    //         }

    //         if ($_FILES["media-vid"]["size"] > 500000000000000) {
    //             $uploadOk = 0;
    //             echo "Sorry, your file is too large.";
    //         }

    //         // Check if $uploadOk is set to 0 by an error
    //         if ($uploadOk == 0 && isset($format_error)) {

    //             echo $message;

    //             // if everything is ok, try to upload file

    //         } else if ($uploadOk == 0) {


    //             echo "Sorry, your video was not uploaded.";

    //         }

    //         else {

    //             $target_filevid = strtr($target_filevid, 'ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ', 'AAAAAACEEEEIIIIOOOOOUUUUYaaaaaaceeeeiiiioooooouuuuyy');
    //             $target_filevid = preg_replace('/([^.a-z0-9]+)/i', '_', $target_filevid);

    //             if (!move_uploaded_file($_FILES["media-vid"]["tmp_name"], $target_dirvid . $target_filevid)) {

    //                 echo "Sorry, there was an error uploading your file. Please retry.";
    //             } else {

    //                 $vid = $target_dirvid . $target_filevid;

    //             }
    //         }
    //     }

    // }
?>
