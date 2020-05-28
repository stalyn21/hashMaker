import matplotlib.pyplot as plt

def average(data):
    p = sum(data)/ float(len(data))
    return p
    

def graphics():
    dificulty=5
    t=1
    #brute force 
    x=[1,2,3,4,5]
    #times is a Matrix of Dificulty x simulaation number
    tim=[ [0.0015, 0, 0, 0.0015, 0.001236, 0.000148, 0.001646, 0.000633, 0.000332], #dificulty1
            [0.016, 0.015, 0.046, 0.015, 0.046, 0.031, 0.047, 0.046, 0.015, 0.045], #dificulti2
            [0.031, 0.125, 0.031, 0.047, 0.156, 0.046, 0.125, 0.219, 0.156, 0.046],
            [7.062, 3.796, 2.765, 1.750, 4.156, 4,000, 10.563, 1.359, 4.203, 5.062],
            [16.172, 15.968, 41.253, 45.093,  26.171, 23.187, 22.578, 24.703, 58.328, 21.468]
            ]
    for i in range(dificulty):
        y.append(average(tim[i]))
 
    plt.figure(1)
    plt.plot(x,y,'.-',linewidth=0.5)
    plt.title("Brute Force Algorithm")
    plt.yscale('log') 
    plt.xlabel('Nonce difficulty')
    plt.ylabel('Run time (second)')
    plt.savefig(f'bruteForce.png', bbox_inches='tight')
    t+=1

    #set transaction
    #times is a Matrix of Dificulty x simulaation number
    tim1=[ [0.02235, 0.3095, 0.193575, 0.1005, 0.2023, 0.171, 0.03125, 0.109375, 0.171875, 0.06745], #dificulty1
            [0.4457, 0.82335, 0.62301, 0.2835,0.78225, 0.892,0.3125, 0.90625, 0.75001, 0.06745], #dificulti2
            [318.434, 23.9688, 33.5439, 209.84, 21.88, 32.69, 218.984, 18.9688, 35.0469, 0.06745],
            [602.26, 88.792, 89.12, 790.765, 76.98, 89.22, 519.765, 64.998, 93.22, 79.32],
            [714.23, 762.2, 698.20, 1202.1, 987.4, 975.32, 1000.2, 640.4, 575.28, 788.9]
            ]
    for i in range(dificulty):
        y1.append(average(tim1[i]))

    plt.figure(2)
    plt.plot(x1,y1,'.-',linewidth=0.5)
    plt.title("Set Transaction Algorithm")
    plt.yscale('log') 
    plt.xlabel('Nonce difficulty')
    plt.ylabel('Run time (second)')
    plt.savefig(f'setTransaction.png', bbox_inches='tight')
    t+=1

    #keccak 
    #times is a Matrix of Dificulty x simulaation number
    times=[ [0.000289, 0.00053, 0.00126, 0.000625, 0.000206, 0.001236, 0.000148, 0.001646, 0.000633, 0.000332], #dificulty1
            [0.003403, 0.001912, 0.002114, 0.009816, 0.003576, 0.009104, 0.001424, 0.006041, 0.000152, 0.005149], #dificulti2
            [0.028151, 0.006007, 0.015136, 0.03055, 0.050129, 0.162268, 0.059446, 0.117252, 0.045493, 0.004907],
            [0.668837, 0.898699, 0.074732, 0.246452, 1.23624, 1.13399, 0.238093, 0.614927, 6.75782, 6.79635],
            [21.29426, 39.5351, 22.7575, 18.9422, 36.6044, 38.4772, 12.0007, 17.2476, 13.2872, 49.0091]
            ]
    for i in range(dificulty):
        y2.append(average(times[i]))

    plt.figure(3)
    plt.plot(x2,y2,'.-', linewidth=0.5)
    plt.title("Keccak Algorithm")
    plt.yscale('log')
    plt.xlabel('Nonce difficulty')
    plt.ylabel('Run time (second)')
    plt.savefig(f'keccak.png', bbox_inches='tight')
    t+=1

    print("Average Times of Brute Force: ", y)
    print("Average Times of Set transaction: ", y1)
    print("Average Times of Keccak: ", y2)
   
    plt.figure(4)
    plt.plot(x,y,'red',label='Brute Force Algorithm',linewidth=0.5)
    plt.plot(x2,y2,label='Keccak Algorithm', linewidth=0.5)
    plt.plot(x1,y1,'green',label='Set Transaction Algorithm',linewidth=0.5)
    plt.title("Comparative Algorithms")
    plt.legend()
    plt.yscale('log')
    #plt.ylim(799, 804) 
    plt.xlabel('Nonce difficulty')
    plt.ylabel('Run time (second)')
    plt.savefig(f'comparativeAlgorithms.png', bbox_inches='tight')
    plt.show()

x=[1,2,3,4,5]
x1=[1,2,3,4,5]
x2=[1,2,3,4,5]
y=[]
y1=[]
y2=[]
graphics()

