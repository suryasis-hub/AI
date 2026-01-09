
import torch, torchvision, numpy 
import matplotlib.pyplot as plt
from torchvision import datasets, transforms
from torch.utils.data import random_split
import torch.nn as nn

model = nn.Sequential(
    nn.Conv2d(1, 2, 3),
    nn.ReLU(),
    nn.MaxPool2d(2),
    nn.Conv2d(2, 4, 3),
    nn.ReLU(),
    nn.MaxPool2d(2),
    nn.Conv2d(4, 8, 3),
    nn.Flatten(),
    nn.Linear(72, 10)
)

model.load_state_dict(torch.load("mnist_conv2d_maxpool.pth"))

test_ds = datasets.MNIST(
    root="data",
    train=False,
    download=True,
    transform=transforms.ToTensor()
)
#print(test_ds.size)
true_count = 0
false_count = 0
for img_test_first, img_test_first_label in test_ds:
    #img_test_first, img_test_first_label = test_ds[i]
    img_test_first = img_test_first.unsqueeze(0)
    results = model(img_test_first)
    count_max = -1
    value_max = -10000
    count = 0
    for el in results[0]:
        if (value_max < el):
            value_max = el
            count_max = count
        count += 1
    if (img_test_first_label == count_max):
        true_count += 1
    else:
        false_count += 1
accuracy = true_count*1.0/(true_count + false_count)
print(f"Final accuracy {accuracy}")
