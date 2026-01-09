import torch, torchvision, numpy 
import matplotlib.pyplot as plt
from torchvision import datasets, transforms
from torch.utils.data import random_split
import torch.nn as nn
from torch.utils.data import DataLoader

print('Libraries installed')

dataset = datasets.MNIST(root='data', download=True, transform = transforms.ToTensor())

print('Loaded data set')

img_train_first , img_train_first_label = dataset[0]

model = nn.Sequential(
    nn.Conv2d(1, 2, 3),
    nn.ReLU(),
    nn.Conv2d(2, 4, 3),
    nn.ReLU(),
    nn.Conv2d(4, 8, 3),
    nn.Flatten(),
    nn.Linear(3872, 10)
)

optimizer = torch.optim.SGD(model.parameters(), lr = 0.005)
criterion = nn.CrossEntropyLoss()

train_loader = DataLoader(dataset)

epochs = 30


for epoch in range(0, epochs):
    total_loss = 0
    for images, labels in train_loader:
        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        total_loss += loss.item()
        optimizer.step()
    avg_loss = total_loss/60000
    print(f"Average loss is {avg_loss}")

torch.save(model.state_dict(), "mnist_conv2d.pth")


