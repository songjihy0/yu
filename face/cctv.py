import cv2

url = 'rtsp://admin:abc12345@192.168.1.64'

cap = cv2.VideoCapture(url)

while cap.isOpened():
    ret, frame = cap.read()
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
