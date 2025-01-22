import requests
from bs4 import BeautifulSoup
def printSecret(coords: dict):
    max_x = max(key[0] for key in coords.keys())
    max_y = max(key[1] for key in coords.keys())

    grid = [[' ' for _ in range(max_x + 1)] for _ in range(max_y + 1)]

    for (x, y), char in coords.items():
        grid[y][x] = char

    for row in grid:
        print(''.join(row))
def decodeSecret(url: str):
    response = requests.get(url)
    response.raise_for_status()
    soup = BeautifulSoup(response.text, 'html.parser')

    table = soup.find('table')
    if not table:
        print("No table found in the Google Doc.")
        return

    coordinates = {}
    rows = table.find_all('tr')
    for row in rows[1:]:
        cells = row.find_all('td')
        x = int(cells[0].text.strip())
        char = cells[1].text.strip()
        y = int(cells[2].text.strip())
        coordinates[(x, y)] = char

    printSecret(coordinates)


url = "https://docs.google.com/document/d/e/2PACX-1vQGUck9HIFCyezsrBSnmENk5ieJuYwpt7YHYEzeNJkIb9OSDdx-ov2nRNReKQyey-cwJOoEKUhLmN9z/pub"  # Replace with the public Google Doc URL
decodeSecret(url)
