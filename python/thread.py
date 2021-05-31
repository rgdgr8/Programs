from threading import *
import random

class appointment:
	def patient(self):
		condition_object.acquire()
		for _ in range(2):
			print('patient john waiting for appointment')
			condition_object.notify()
			condition_object.wait() # Thread is in waiting state
			print('patiend john successfully got the appointment')
		condition_object.notify()
		condition_object.release()
		print('patient john is done')

	def doctor(self):
		condition_object.acquire()
		for _ in range(2):
			print('doctor jarry checking the time for appointment')
			time=random.randint(1,13)
			print('oppointed time is {} PM'.format(time))
			condition_object.notify()
			print('doctor is going to wait')
			condition_object.wait()
		condition_object.release()
		print('doctor is done')
	
condition_object = Condition()
class_obj=appointment()

T1 = Thread(target=class_obj.patient)
T2 = Thread(target=class_obj.doctor)

T1.start()
T2.start()

T1.join()
T2.join()
print("\nEND\n")
