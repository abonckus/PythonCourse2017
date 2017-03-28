import pymysql as sql
import os


class Beer:
    def __init__(self, name, manufacturer, beer_type):
        self.name = name
        self.manufacturer = manufacturer
        self.type = beer_type


class BeersManager:
    db = sql.connect(host="localhost", user="testuser", passwd="password", db="python_course")
    cursor = db.cursor()

    def create_table(self):
        print('Creating table...')
        query = 'CREATE TABLE beers (beer_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ' \
                'beer_name TEXT, manufacturer TEXT, beer_type TEXT);'
        self.cursor.execute(query)

    def fill_table(self, beers):
        print('Inserting data to table...')
        for b in beers:
            query = 'INSERT INTO beers(beer_name, manufacturer, beer_type) ' \
                    'VALUES("'+b.name+'", "'+b.manufacturer+'", "'+b.type+'");'
            self.cursor.execute(query)

    def delete_beer(self, beer_id):
        print('Deleting beer id: ' + str(beer_id) + '...')
        query = 'DELETE FROM beers WHERE beer_id = ' + str(beer_id) + ';'
        self.cursor.execute(query)

    def delete_all(self):
        print('Deleting all beers...')
        query = 'TRUNCATE beers;'
        self.cursor.execute(query)

    def destroy_table(self):
        print('Destroying table beers...')
        query = 'DROP TABLE beers;'
        self.cursor.execute(query)

    def print_beers(self):
        query = 'SELECT * FROM beers;'
        self.cursor.execute(query)
        result = self.cursor.fetchall()
        for r in result:
            print(r)

    def close(self):
        self.db.close()

manager = BeersManager()
beers = []
cmd = 99

while cmd != 0:
    print('1.Create table\n'
          '2.Create a beer\n'
          '3.Fill table\n'
          '4.Print beers\n'
          '5.Delete beer\n'
          '6.Delete all beers\n'
          '7.Destroy table\n'
          '8.Clear screen\n'
          '0.Exit\n')
    cmd = int(input())
    if cmd == 1:
        manager.create_table()
    if cmd == 2:
        print('New beer')
        print('Name: ')
        n = input()
        print('Manufacturer: ')
        m = input()
        print('Beer type: ')
        t = input()
        beer = Beer(n, m, t)
        beers.append(beer)
    if cmd == 3:
        manager.fill_table(beers)
    if cmd == 4:
        manager.print_beers()
    if cmd == 5:
        print('Delete beer')
        print('ID: ')
        beer_id = int(input())
        manager.delete_beer(beer_id)
    if cmd == 6:
        manager.delete_all()
    if cmd == 7:
        manager.destroy_table()
    if cmd == 8:
        os.system('cls')
