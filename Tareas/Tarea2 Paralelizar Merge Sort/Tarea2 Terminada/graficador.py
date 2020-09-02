import matplotlib.pyplot as plt

#leer los datos
paralelosdat = open('paralelos.dat' , 'r').read()
serialesdat = open('seriales.dat' , 'r').read()



#para meter los datos en un vector
str = ""
vectorDatosParalelo = []
for i in paralelosdat:
    if(i != '\n'):
        str = str+i
    else:
        print (str)
        vectorDatosParalelo.append(float(str))
        str = ''

str2=""
vectorDatosSerial = []
for i in serialesdat:
    if(i != '\n'):
        str2 = str2+i
    else:
        print (str2)
        vectorDatosSerial.append(float(str2))
        str2 = ''

VectorSpeedup = []
for i in range(0,len(vectorDatosSerial)):
    speedup = vectorDatosSerial[i]/vectorDatosParalelo[i]
    VectorSpeedup.append(speedup)

ejex = []
for i in range(0,10000000):
    ejex.append(i*100000)
#graficas
plt.plot(VectorSpeedup)
plt.plot(vectorDatosParalelo)
plt.plot(vectorDatosSerial)
plt.ylabel("tiempo")
plt.xlabel('tamaño del vector(de 0 a 10.000.000) \n \ngrafica de tiempos en el servidor de HPC de la universidad \n con 100 vectores de tamaño 1 hasta 10.000.000\n (naranja = paralelo) (azul = serial) , verde(speedup)')
plt.show()
