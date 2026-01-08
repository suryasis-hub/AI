import torch, torchvision, numpy 
import matplotlib.pyplot as plt
from torchvision import datasets, transforms
from torch.utils.data import random_split
import torch.nn as nn

print('Libraries installed')
dataset = datasets.MNIST(root='data', download=True, transform = transforms.ToTensor())
train_ds, val_ds = random_split(dataset, [59400, 600])
img_train_first, img_train_first_label = train_ds[0]
print(type(train_ds[0]))
print(type(img_train_first_label))
img_train_first = img_train_first.unsqueeze(0)
model = nn.Sequential(
    nn.Flatten(),
    nn.Linear(784, 128),
    nn.ReLU(),
    nn.Linear(128, 10)
)

optimizer = torch.optim.SGD(model.parameters(), lr = 0.05)
criterion = nn.CrossEntropyLoss()
epochs = 5
for epoch in range(0, epochs):
    total_loss = 0.0
    print(f"Doing with {epoch} epochs")
    for i in range(0, 59400):
        optimizer.zero_grad()
        #print (f"   Doing {i}th example")
        img_train_curr, img_train_curr_label  = train_ds[i]
        results = model(img_train_curr.unsqueeze(0))
        loss = criterion(results, torch.tensor(img_train_curr_label).unsqueeze(0))
        loss.backward()
        optimizer.step()
        total_loss += loss.item()
    avg_loss = total_loss/59400
    print(f"Average loss is {avg_loss}")
torch.save(model.state_dict(), "mnist_dense.pth")
