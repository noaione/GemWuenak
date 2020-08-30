import random
import time

diamond = ["10♦", "J♦", "Q♦", "K♦", "A♦"]
heart = ["10♥", "J♥", "Q♥", "K♥", "A♥"]
spade = ["10♠", "J♠", "Q♠", "K♠", "A♠"]
club = ["10♣", "J♣", "Q♣", "K♣", "A♣"]  # var2 ini sebenernya gk dibutuhin, cm biar gampang copas

kartuTanganPlayer = []
kartuTanganBot = []
kartuDeck = [
    "A♣",
    "2♣",
    "3♣",
    "4♣",
    "5♣",
    "6♣",
    "7♣",
    "8♣",
    "9♣",
    "10♣",
    "J♣",
    "Q♣",
    "K♣",
    "A♦",
    "2♦",
    "3♦",
    "4♦",
    "5♦",
    "6♦",
    "7♦",
    "8♦",
    "9♦",
    "10♦",
    "J♦",
    "Q♦",
    "K♦",
    "A♥",
    "2♥",
    "3♥",
    "4♥",
    "5♥",
    "6♥",
    "7♥",
    "8♥",
    "9♥",
    "10♥",
    "J♥",
    "Q♥",
    "K♥",
    "A♠",
    "2♠",
    "3♠",
    "4♠",
    "5♠",
    "6♠",
    "7♠",
    "8♠",
    "9♠",
    "10♠",
    "J♠",
    "Q♠",
    "K♠",
]
kartuStack = []
looper = True


def checker(whichPlayer):  # check apakah udh 41 apa belom
    global flag
    flag = False
    if whichPlayer == 1:
        total = 0
        simbol = kartuTanganPlayer[0][-1]
        for i in kartuTanganPlayer:
            if i[-1] == simbol:
                sama = True
            else:
                sama = False
                break

        if sama:
            for i in kartuTanganPlayer:
                if i[0] == "J":
                    total += 10
                elif i[0] == "Q":
                    total += 10
                elif i[0] == "K":
                    total += 10
                elif i[0] == "A":
                    total += 11
                elif len(i) == 3:
                    total += 10
                else:
                    total += int(i[0])
            if total == 41:
                print("player 1 menang")
                flag = True
    else:
        totalbot = 0
        simbolbot = kartuTanganBot[0][-1]
        for i in kartuTanganBot:
            if i[-1] == simbolbot:
                samabot = True
            else:
                samabot = False
                break
        if samabot:
            for i in kartuTanganBot:
                if i[0] == "J":
                    totalbot += 10
                elif i[0] == "Q":
                    totalbot += 10
                elif i[0] == "K":
                    totalbot += 10
                elif i[0] == "A":
                    totalbot += 11
                elif len(i) == 3:
                    totalbot += 10
                else:
                    totalbot += int(i[0])
            if totalbot == 41:
                print("player bot menang")
                flag = True


def BotTurn():  # giliiran bot, masih bodoh (random)
    global total
    print("giliran bot!")
    drawKartu(2)
    buangbot = random.choice(kartuTanganBot)
    kartuStack.append(buangbot)
    kartuTanganBot.remove(buangbot)
    print_stack()
    checker(2)
    waiting()


def PemainTurn():  # giliran pemain
    global total
    print_Tangan("awal")
    while True:
        drawing = input("ambil dari stack or deck (s/d)?\n")
        if drawing == "s":  # jika ambil dari stack
            kartuTanganPlayer.append(kartuStack[-1])
            kartuStack.remove(kartuStack[-1])
            break
        elif drawing == "d":  # jika ambil dari deck
            drawKartu(1)
            break
        else:
            print("hah gimana?")
    print_Tangan("akhir")
    while True:
        try:
            keluaran = int(input("keluarin kartu ke-:"))  # buang kartu no. brp
            buangan = kartuTanganPlayer[keluaran - 1]
            kartuStack.append(buangan)
            kartuTanganPlayer.remove(buangan)
            print_stack()
            checker(1)
            waiting()
            break
        except ValueError:
            print("yang bener boss... 1-5!")


def waiting():  # jeda dari turn player ke berikutnya
    for i in range(2):
        print(".")
        time.sleep(0.25)


def drawKartu(whichPlayer):  # ambil random dari deck, masuk ke tangan
    if whichPlayer == 1:
        salahSatu = random.choice(kartuDeck)
        kartuTanganPlayer.append(salahSatu)
        kartuDeck.remove(salahSatu)
    else:
        salahSatu = random.choice(kartuDeck)
        kartuTanganBot.append(salahSatu)
        kartuDeck.remove(salahSatu)


def setupGame():  # bagi 4 kartu ke player&bot
    for i in range(4):
        drawKartu(1)
        drawKartu(2)
    stackpertama = random.choice(kartuDeck)
    kartuStack.append(stackpertama)
    kartuDeck.remove(stackpertama)
    print_stack()


def print_Tangan(masa):
    if masa == "awal":  # print kartu tangan sebelum draw
        print("kartu tangan:")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11)
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |")
        print("    %s " % kartuTanganPlayer[0], end=" ")
        print("        %s " % kartuTanganPlayer[1], end=" ")
        print("        %s " % kartuTanganPlayer[2], end=" ")
        print("        %s " % kartuTanganPlayer[3])
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11)
        print("    (1)     ", end=" ")
        print("   (2)     ", end=" ")
        print("   (3)     ", end=" ")
        print("   (4)     ")
    else:  # print kartu tangan setelah draw
        print("\nkartu tangan:")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11)
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |")
        print("    %s " % kartuTanganPlayer[0], end=" ")
        print("        %s " % kartuTanganPlayer[1], end=" ")
        print("        %s " % kartuTanganPlayer[2], end=" ")
        print("        %s " % kartuTanganPlayer[3], end=" ")
        print("        %s " % kartuTanganPlayer[4])
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |", end=" ")
        print("|	      |", end=" ")
        print("|	  |")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11, end=" ")
        print("=" * 11)
        print("    (1)     ", end=" ")
        print("   (2)     ", end=" ")
        print("   (3)     ", end=" ")
        print("   (4)     ", end=" ")
        print("   (5)     ")


def print_stack():  # print kartu tumpukan sebelum dan setelah dibuang
    print("\nstack:")
    print("=" * 11)
    print("|	  |")
    print("|	  |")
    print("|	  |")
    print("    %s" % kartuStack[-1])
    print("|	  |")
    print("|	  |")
    print("|	  |")
    print("=" * 11)


if __name__ == "__main__":
    global flag
    setupGame()
    while looper:
        PemainTurn()
        if flag:  # kalo kartu udah 41, flag=True, kebreak
            break
        BotTurn()
        if flag:
            break
    print("permainan telah berakhir")
