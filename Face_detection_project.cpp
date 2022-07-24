#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	cout << "Welcome to SAGAR'S Project !!!!" << endl;
	cout << "This project can detect faces in " << endl;
	cout << "\t1. an image." << endl;
	cout << "\t2. a video." << endl;
	cout << "\t3. a webcam." << endl;
	do
	{
		int choice;
		cout << "1. Image" << endl;
		cout << "2. Video" << endl;
		cout << "3. Webcam" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice (1 - 4) : ";
		cin >> choice;
		switch (choice)
		{
			case 1: {
				string path;
				cout << "Enter path of the image : " << endl;
				cin >> path;
				Mat img = imread(path);
				resize(img, img, Size(), 0.8, 0.8);
				CascadeClassifier facecascade;
				facecascade.load("Resources/haarcascade_frontalface_default.xml");
				if (facecascade.empty())
				{
					cout << "XML file cann't be loaded." << endl;
				}
				vector<Rect> faces;
				facecascade.detectMultiScale(img, faces, 1.1, 10);
				for (int i = 0; i < faces.size(); i++)
				{
					rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 3);
					putText(img, "Face", Point(faces[i].tl().x, faces[i].tl().y - 5), 
						FONT_HERSHEY_PLAIN, 2, Scalar(255, 0, 0), 2);
				}
				imshow("Face detection", img);
				waitKey(0);
				break;
			}
			case 2: {
				string path;
				cout << "Enter path of the video : " << endl;
				cin >> path;
				VideoCapture cap(path);
				Mat img;
				CascadeClassifier facecascade;
				facecascade.load("Resources/haarcascade_frontalface_default.xml");
				if (facecascade.empty())
				{
					cout << "XML file cann't be loaded" << endl;
				}
				vector<Rect> faces;
				while (true)
				{
					cap.read(img);
					resize(img, img, Size(), 0.5, 0.5);
					facecascade.detectMultiScale(img, faces, 1.1, 10);
					for (int i = 0; i < faces.size(); i++)
					{
						rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 3);
						putText(img, "Face", Point(faces[i].tl().x, faces[i].tl().y - 5),
							FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 255), 2);
					}
					if (!img.empty())
					{
						imshow("Face Detection", img);
						waitKey(1);
					}
					else
						destroyWindow("Face Detection");
				}
				break;
			}
			case 3: {
				VideoCapture cap(0);
				Mat img;
				CascadeClassifier facecascade;
				facecascade.load("Resources/haarcascade_frontalface_default.xml");
				if (facecascade.empty())
				{
					cout << "XML file cann't be loaded." << endl;
				}
				vector<Rect> faces;
				while (true)
				{
					cap.read(img);
					facecascade.detectMultiScale(img, faces, 1.1, 10);
					for (int i = 0; i < faces.size(); i++)
					{
						rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 0, 255), 3);
						putText(img, "Face", Point(faces[i].tl().x, faces[i].tl().y - 5),
							FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2);
					}
					if (!img.empty())
					{
						imshow("Face Detection", img);
						waitKey(1);
					}
					else
						destroyWindow("Face Detection");
				}
				break;
			}
			case 4: 
				exit(0);
			default:
				break;
		}
	} while (1);
	return 0;
}