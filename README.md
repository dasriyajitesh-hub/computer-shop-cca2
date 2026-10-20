# Computer Shop — CCA 2 CI/CD (C++)

This repository uses the existing Computer Shop C++ project and packages a small C++ HTTP interface so it can be accessed in a browser after Kubernetes deployment. The container does not use Python.

## Technology stack
C++17, GitHub, Jenkins, Docker, Amazon ECR, AWS EC2, Minikube and Kubernetes.

## CCA 2 pipeline stages
1. **Checkout:** Jenkins pulls the latest source from GitHub.
2. **Build and Test:** compile `COMPSHOP.cpp` and `webserver.cpp` using g++.
3. **Docker Build:** create a container image containing the compiled C++ web server.
4. **Push Image to Amazon ECR:** authenticate with AWS credentials stored in Jenkins and push a build-number tag plus `latest`.
5. **Deploy to Minikube:** apply Kubernetes Deployment and Service manifests.
6. **Verify Application:** check the rollout, Pods and Service; open the app using the Minikube service URL.

## Before running Jenkins
- Create an ECR repository named `computer-shop` in `ap-south-1` (or change `AWS_REGION` in `Jenkinsfile`).
- Replace `YOUR_AWS_ACCOUNT_ID` in `Jenkinsfile` with your 12-digit AWS account ID.
- Add Jenkins AWS credentials with ID `aws-ecr-credentials` using an AWS Credentials-type credential with permission to push to ECR.
- Ensure the Jenkins agent has Docker, AWS CLI, `kubectl`, and Minikube configured and can access the cluster.
- The Deploy stage refreshes the Kubernetes `ecr-registry-secret` from ECR credentials before applying the Deployment. ECR authorization tokens expire, so the pipeline refreshes the secret on each run. The Jenkins agent needs AWS CLI access to the same AWS account/region and access to the Minikube cluster.
- Push this repository to GitHub and create a Jenkins Pipeline job connected to that repository.

## Local build / run
```bash
g++ -std=c++17 -O2 COMPSHOP.cpp -o compshop
g++ -std=c++17 -O2 webserver.cpp -o computer-shop-server
./computer-shop-server
```
Open `http://localhost:5000` in a browser. Press Ctrl+C to stop the server.

## Kubernetes verification
```bash
kubectl get pods
kubectl get deployment,service
minikube service computer-shop --url
```

## Required second-run demonstration
After the first successful pipeline, change the visible heading or message in `webserver.cpp`, commit and push the change, then run Jenkins again. Show that the second build has a new image tag and the updated page is served.

## Files
- `COMPSHOP.cpp`: original Computer Shop console project.
- `webserver.cpp`: C++ HTTP interface and `/health` endpoint.
- `Dockerfile`: multi-stage C++ build and runtime image.
- `Jenkinsfile`: automated build, test, ECR push, deployment and verification.
- `k8s/deployment.yaml`, `k8s/service.yaml`: Kubernetes resources.
