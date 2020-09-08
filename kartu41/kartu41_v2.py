import os
import random
import time


class Kartu41:
    def __init__(self):
        self._card_set = [
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

        self._player_deck = []
        self._bot_deck = []
        self._player_stack = []
        self._bot_stack = []

        self.winner = -1
        self._score_player = 0
        self._score_bot = 0

        self.gameover = False

    def start_game(self):
        self.clear_screen()
        print("Membagikan kartu...")
        for _ in range(4):
            self._player_deck.append(self._draw_card())
            self._bot_deck.append(self._draw_card())
        print("Memeriksa kartu awal...")
        self.check_card_score()
        print("Memulai game...")
        while not self.gameover:
            self.clear_screen()
            try:
                self.player_turn()
                self.check_card_score()
            except (SystemError, SystemExit, KeyboardInterrupt):
                self.check_card_score()
                self.gameover = True
            if self.gameover:
                break
            self._print_wait()
            self.clear_screen()
            try:
                self.bot_turn()
                self.check_card_score()
            except (SystemError, SystemExit, KeyboardInterrupt):
                self.check_card_score()
                self.gameover = True
            if self.gameover:
                break
            self._print_wait()

        if self.winner == -1:
            if self._score_player == self._score_bot:
                self.winner = 2
            elif self._score_player > self._score_bot:
                self.winner = 0
            else:
                self.winner = 1

        if self.winner == 0:
            print("Pemenangnya adalah pemain!")
            print("Skor akhir:")
            print("\tPlayer: {}\n\tBot: {}".format(self._score_player, self._score_bot))
        elif self.winner == 1:
            print("Pemenangnya adalah bot!")
            print("Skor akhir:")
            print("\tPlayer: {}\n\tBot: {}".format(self._score_player, self._score_bot))
        elif self.winner == 2:
            print("Permainan seri!")
            print("Skor akhir:")
            print("\tPlayer: {}\n\tBot: {}".format(self._score_player, self._score_bot))

    def clear_screen(self):
        if os.name in ["nt", "win", "win32"]:
            os.system("cls")
        else:
            os.system("clear")

    def _print_wait(self):
        for _ in range(3):
            print(".", end=" ")
            time.sleep(0.25)
        print("")

    def player_turn(self):
        print("-+- Giliran Pemain! -+-\n")
        self.print_stack()
        print("")
        self.print_card()
        if len(self._player_stack) < 1:
            print("\nMengambil dari deck...")
            self._card_controller(0, 0, self._draw_card())
        else:
            while True:
                get_from = input("Ambil dari (s)tack apa (d)eck? (s/d) -> ")
                get_from = get_from.lower()
                if get_from == "s":
                    self._card_controller(0, 0, self._stack_controller(0, 1))
                    break
                elif get_from == "d":
                    self._card_controller(0, 0, self._draw_card())
                    break
                else:
                    print("Hah gimana?")
        print("")
        self.print_card()
        print("")

        while True:
            throw_card = input("Keluarin kartu ke-")
            if throw_card.isdigit():
                throw_card = int(throw_card)
                if throw_card >= 1 and throw_card <= 5:
                    card_throwen = self._player_deck[throw_card - 1]
                    self._stack_controller(1, 0, card_throwen)
                    self._card_controller(0, 1, card_throwen)
                    break
            print("Yang bener boss... 1-5!")

    def bot_turn(self):
        print("-+- Giliran bot! -+-")
        self._print_wait()
        do_stack, card_pos = self.__bot_do_stack()
        if do_stack:
            print("Bot mengambil kartu dari stack...")
            card = self._stack_controller(1, 1)
        else:
            card = self._draw_card()
        self._card_controller(1, 0, card)
        self._print_wait()
        if do_stack:
            throw_card = self._bot_deck[card_pos]
        else:
            throw_card = self.__bot_decide_throw(card)
        self._card_controller(1, 1, throw_card)
        self._stack_controller(0, 0, throw_card)

    def print_stack(self):
        if len(self._player_stack) < 1:
            print("Tidak ada kartu di stack yang bisa diambil.")
            return
        print("Kartu Stack:")
        print("=" * 11)
        print("|	  |")
        print("|	  |")
        print("    {}".format(self._player_stack[-1]))
        print("|	  |")
        print("|	  |")
        print("=" * 11)

    def _print_thing(self, card_cc):
        for _ in range(2):
            print("|	  |", end=" ")
            print("|	      |", end=" ")
        if card_cc == 5:
            print("|	  |")
        else:
            print("")

    def print_card(self):
        print("Kartu Tangan:")
        deck_total = len(self._player_deck)
        for _ in range(deck_total):
            print("=" * 11, end=" ")
        print("")
        self._print_thing(deck_total)
        self._print_thing(deck_total)
        print("    {} ".format(self._player_deck[0]), end=" ")
        for i in range(1, deck_total):
            print("        {} ".format(self._player_deck[i]), end=" ")
        print("")
        self._print_thing(deck_total)
        self._print_thing(deck_total)
        for _ in range(deck_total):
            print("=" * 11, end=" ")
        print("")
        for i in range(deck_total):
            print("    ({})     ".format(i + 1), end="")
        print("")

    def _draw_card(self):
        if len(self._card_set) < 2:
            card = self._card_set[0]
            self._card_set = []
            return card
        card = random.choice(self._card_set)
        self._card_set.remove(card)
        return card

    def _stack_controller(self, player, mode, card=0):
        if mode == 0:
            if player == 0:
                self._player_stack.append(card)
            elif player == 1:
                self._bot_stack.append(card)
        elif mode == 1:
            if player == 0:
                return self._player_stack.pop(-1)
            elif player == 1:
                return self._bot_stack.pop(-1)

    def _card_controller(self, player, mode, card=0):
        if mode == 0:
            if player == 0:
                self._player_deck.append(card)
            elif player == 1:
                self._bot_deck.append(card)
        elif mode == 1:
            if player == 0:
                self._player_deck.remove(card)
            elif player == 1:
                self._bot_deck.remove(card)

    def check_card_score(self):
        player_set = {"♦": 0, "♥": 0, "♠": 0, "♣": 0}
        self._score_player = 0
        for deck in self._player_deck:
            sc = deck[-1]
            if sc not in player_set:
                player_set[sc] = 0
            player_set[sc] += self._card_to_num(deck)

        bot_set = {"♦": 0, "♥": 0, "♠": 0, "♣": 0}
        self._score_bot = 0
        for deck in self._bot_deck:
            sc = deck[-1]
            if sc not in bot_set:
                bot_set[sc] = 0
            bot_set[sc] += self._card_to_num(deck)

        p_i = 0
        b_i = 0
        player_keys = list(player_set.keys())
        bot_keys = list(bot_set.keys())
        for i in range(1, 4):
            if player_set[player_keys[i]] > player_set[player_keys[i - 1]]:
                p_i = i
            if bot_set[bot_keys[i]] > bot_set[bot_keys[i - 1]]:
                b_i = i

        for i in range(4):
            if i == p_i:
                self._score_player += player_set[player_keys[i]]
            else:
                self._score_player -= player_set[player_keys[i]]
            if i == b_i:
                self._score_bot += bot_set[bot_keys[i]]
            else:
                self._score_bot -= bot_set[bot_keys[i]]

        if self._score_player >= 41:
            self.winner = 0
            self.gameover = True
        elif self._score_bot >= 41:
            self.winner = 1
            self.gameover = True
        elif len(self._card_set) == 0:
            if self._score_player == self._score_bot:
                self.winner = 2
            elif self._score_player > self._score_bot:
                self.winner = 0
            else:
                self.winner = 1
            self.gameover = True

    def _card_to_num(self, card: str) -> int:
        """Convert card string to number

        :param card: card to convert
        :type card: str
        :return: card amount
        :rtype: int
        """
        if card[0] in ["K", "Q", "J"]:
            return 10
        elif card[0] == "A":
            return 11
        else:
            return int(card[:-1])

    # From this function forward, it's all Bot deciding system

    def __bot_do_stack(self):
        """
        Decide if bot should get from stack or deck.
        """
        if len(self._bot_stack) < 1:
            return False, -1
        stack_card_suites = self._bot_stack[-1][-1]
        stack_card_amount = self._card_to_num(self._bot_stack[-1])
        bot_set = {"♦": 0, "♥": 0, "♠": 0, "♣": 0}
        for deck in self._bot_deck:
            sc = deck[-1]
            if sc not in bot_set:
                bot_set[sc] = 0
            bot_set[sc] += self._card_to_num(deck)

        highest_suite = "♦"
        highest_score = bot_set["♦"]
        for suite, scores in bot_set.items():
            if scores > highest_score:
                highest_suite = suite
                highest_score = scores

        if stack_card_suites != highest_suite:
            return False, -1

        same_suites = True
        for deck in self._bot_deck:
            if deck[-1] != highest_suite:
                same_suites = False
                break

        if same_suites:
            throw_pos = -1
            throw_amount = 11
            for bpos, bcard in enumerate(self._bot_deck):
                bcam = self._card_to_num(bcard)
                if bcam < throw_amount:
                    throw_amount = bcam
                    throw_pos = bpos
            if throw_amount > stack_card_amount:
                return False, -1
            return True, throw_pos

        throw_pos = -1
        throw_amount = 0
        for pos, card in enumerate(self._bot_deck):
            if card[-1] != highest_suite:
                card_amount = self._card_to_num(card)
                if card_amount > throw_amount:
                    throw_pos = pos
                    throw_amount = card_amount

        if throw_pos == -1:
            return False, -1
        return True, throw_pos

    def __bot_decide_throw(self, new_card: str) -> str:
        """Decide what the shittiest card to throw

        :param new_card: the card that are just grabbed.
        :type new_card: str
        :return: shittiest card
        :rtype: str
        """
        bot_set = {"♦": 0, "♥": 0, "♠": 0, "♣": 0}
        for deck in self._bot_deck:
            sc = deck[-1]
            if sc not in bot_set:
                bot_set[sc] = 0
            bot_set[sc] += self._card_to_num(deck)

        highest_suite = "♦"
        highest_score = bot_set["♦"]
        for suite, scores in bot_set.items():
            if scores > highest_score:
                highest_suite = suite
                highest_score = scores

        same_suites = True
        for deck in self._bot_deck:
            if deck[-1] != highest_suite:
                same_suites = False
                break

        if new_card[-1] != highest_suite and same_suites:
            # Throw card from deck because all card is the same
            # and it's useless since it's different suites
            return new_card

        new_card_amount = self._card_to_num(new_card)
        if same_suites:
            throw_pos = -1
            throw_amount = 11
            for bpos, bcard in enumerate(self._bot_deck):
                bcam = self._card_to_num(bcard)
                if bcam < throw_amount:
                    throw_amount = bcam
                    throw_pos = bpos
            if throw_amount > new_card_amount:
                return new_card
            return self._bot_deck[throw_pos]

        throw_pos = -1
        throw_amount = 0
        for bpos, bcard in enumerate(self._bot_deck):
            if bcard[-1] != highest_suite:
                bcam = self._card_to_num(bcard)
                if bcam > throw_amount:
                    throw_amount = bcam
                    throw_pos = bpos

        if new_card[-1] != highest_suite:
            if new_card_amount > throw_amount:
                return new_card
        if throw_pos == -1:
            return new_card
        return self._bot_deck[throw_pos]


if __name__ == "__main__":
    kartu = Kartu41()
    kartu.start_game()
